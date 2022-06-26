#include "SelectToolNode.hpp"
#include "ResourceProvider.hpp"
#define PI 3.14159

const int SelectToolNode::MaxToolNodes = 5;
const float SelectToolNode::CircleScale = 0.5;

void SelectToolNode::DrawSelectToolMenuBG(int cx, int cy) const noexcept{
    glUseProgram(progMenuBg);
    glEnableVertexAttribArray(vertex_pPosMenuBg);
    glBindBuffer(GL_ARRAY_BUFFER, VBOMenuBg);

    glUniform2f(viewportPosMenuBg, (float)cx, (float)cy);
    glUniform1f(circle_scalePosMenuBg, CircleScale);

    glVertexAttribPointer(vertex_pPosMenuBg, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(vertex_pPosMenuBg);
    glUseProgram(0);
}

void SelectToolNode::Draw(int cx, int cy, int pos, bool mouseOver) noexcept{
    glUseProgram(progMenuItem);
    glBindTexture(GL_TEXTURE_2D, GetImage());
    glBindBuffer(GL_ARRAY_BUFFER, VBOMenuItem);
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(texPosMenuItem, 0);

    glUniform2f(viewportPosMenuItem, (float)cx, (float)cy);
    glUniform1f(circle_scalePosMenuItem, CircleScale);
    glUniform1f(alphaPosMenuItem, pos / (MaxToolNodes * PI));
    glUniform1i(segment_countPosMenuItem, MaxToolNodes);
    glUniform1i(segmentPosMenuItem, pos);
    glUniform1i(is_mouse_overPosMenuItem, (int)mouseOver);

    glEnableVertexAttribArray(vertex_pPosMenuItem);
    glVertexAttribPointer(vertex_pPosMenuItem, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(vertex_pPosMenuItem);
    glUseProgram(0);
}

bool SelectToolNode::SelectNode(int id) const noexcept{
    if(id < 0 || GetToolNodes().size() <= id) return false;
    GetToolNodes()[id]->Select();
    return true;
}

int SelectToolNode::GetNodeIdByPoint(int cx, int cy, int x, int y) const noexcept{
    float glX = ((x / (float)cx) - 0.5) * 2.0 * (cx / (float)cy);
    float glY = (0.5 - (y / (float)cy)) * 2.0;
    float rVec = sqrt(glX*glX + glY * glY);

    if(rVec < SelectToolNode::CircleScale){
        float sectorAngle = PI / (float)SelectToolNode::MaxToolNodes;
        float rVecAngle;
        if(glX > 0){
            rVecAngle = acos(glY / rVec) * 0.5;
        }
        else{
            rVecAngle = (PI - acos(glY / rVec) * 0.5);
        }
        rVecAngle += sectorAngle * 0.25;
        if(rVecAngle > PI) rVecAngle = rVecAngle - PI;
        int sector = (rVecAngle + (sectorAngle * 0.5)) / sectorAngle;
        return sector;
    }
    return -1;
}

void SelectToolNode::DrawSelectToolMenu(int cx, int cy, int mouseOverTool) noexcept{
    DrawSelectToolMenuBG(cx, cy);
    for(int i = 0 ; i < GetToolNodes().size(); i++)
        GetToolNodes()[i]->Draw(cx, cy, i, i == mouseOverTool);
}

void SelectToolNode::Select() noexcept{ OnSelect();}

SelectToolNode::SelectToolNode() noexcept{
    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    //menu bg program
    glGenBuffers(1, &VBOMenuBg);
    glBindBuffer(GL_ARRAY_BUFFER, VBOMenuBg);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    progMenuBg = BuildShaderProgram(ResourceProvider::GetProvider().GetMenuBgVertex().c_str(), ResourceProvider::GetProvider().GetMenuBgFragment().c_str());
    vertex_pPosMenuBg = glGetAttribLocation(progMenuBg, "vertex_p");
    viewportPosMenuBg = glGetUniformLocation(progMenuBg, "viewport");
    circle_scalePosMenuBg = glGetUniformLocation(progMenuBg, "circle_scale");

    //menu item progtram
    glGenBuffers(1, &VBOMenuItem);
    glBindBuffer(GL_ARRAY_BUFFER, VBOMenuItem);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    progMenuItem = BuildShaderProgram(ResourceProvider::GetProvider().GetMenuItemVertex().c_str(), ResourceProvider::GetProvider().GetMenuItemFragment().c_str());
    
    vertex_pPosMenuItem = glGetAttribLocation(progMenuItem, "vertex_p");
    texPosMenuItem = glGetUniformLocation(progMenuItem, "tex");
    viewportPosMenuItem = glGetUniformLocation(progMenuItem, "viewport");
    circle_scalePosMenuItem = glGetUniformLocation(progMenuItem, "circle_scale");
    alphaPosMenuItem = glGetUniformLocation(progMenuItem, "alpha");
    segment_countPosMenuItem = glGetUniformLocation(progMenuItem, "segment_count");
    segmentPosMenuItem = glGetUniformLocation(progMenuItem, "segment");
    is_mouse_overPosMenuItem = glGetUniformLocation(progMenuItem, "is_mouse_over");
}

SelectToolNode::~SelectToolNode() noexcept{
    glDeleteProgram(progMenuBg);
}

