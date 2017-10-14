#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "cgs/gl_driver_util.hpp"
#include "cgs/scenegraph.hpp"

namespace cgs
{
    //-----------------------------------------------------------------------------------------------
    // Public functions
    //-----------------------------------------------------------------------------------------------
    void set_gl_driver(const gl_driver& driver);
    bool initialize_renderer();
    void finalize_renderer();
    void render(view_id view);
} // namespace cgs

#endif // RENDERER_HPP
