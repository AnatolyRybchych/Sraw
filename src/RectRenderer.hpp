#include "ResourceProvider.hpp"
#include "Coords.hpp"

class RectRenderer{
private:
    static RectRenderer *renderer;

    GLint vertex_p;
    GLint color;
    GLuint VBO;
    GLuint prog;
    
    RectRenderer() noexcept;
public:
    static const RectRenderer &GetRenderer() noexcept;

    void Fill(float r, float g, float b, float a) const noexcept;
    void Fill(const Coords &p1, const Coords &p2, float r, float g, float b, float a) const noexcept;

    ~RectRenderer() noexcept;
};