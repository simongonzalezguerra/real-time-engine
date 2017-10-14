#ifndef GL_DRIVER_UTIL_HPP
#define GL_DRIVER_UTIL_HPP

#include "cgs/gl_driver.hpp"

#include <memory>
#include <vector>

namespace cgs
{
    //-----------------------------------------------------------------------------------------------
    // Default textures
    //-----------------------------------------------------------------------------------------------
    struct default_texture_handle
    {
        default_texture_handle() : m_default_texture_id(0U) {}
        default_texture_handle(gl_texture_id default_texture_id) : m_default_texture_id(default_texture_id) {}
        default_texture_handle(std::nullptr_t) : m_default_texture_id(0U) {}
        operator int() {return m_default_texture_id;}
        operator gl_texture_id() {return m_default_texture_id;}
        bool operator ==(const default_texture_handle &other) const {return m_default_texture_id == other.m_default_texture_id;}
        bool operator !=(const default_texture_handle &other) const {return m_default_texture_id != other.m_default_texture_id;}
        bool operator ==(std::nullptr_t) const {return m_default_texture_id == 0U;}
        bool operator !=(std::nullptr_t) const {return m_default_texture_id != 0U;}

        gl_texture_id m_default_texture_id;
    };

    struct default_texture_deleter
    {
        typedef default_texture_handle pointer;

        default_texture_deleter(gl_driver driver) : m_driver(driver) {}

        template<class other> default_texture_deleter(const other&) {};

        void operator()(pointer p) const
        {
            m_driver.delete_default_texture(p);
        }

        gl_driver m_driver;
    };

    typedef std::unique_ptr<gl_texture_id, default_texture_deleter> unique_default_texture;
    typedef std::vector<unique_default_texture> default_texture_vector;

    unique_default_texture make_default_texture(const gl_driver& driver);

    //-----------------------------------------------------------------------------------------------
    // Textures
    //-----------------------------------------------------------------------------------------------
    struct texture_handle
    {
        texture_handle() : m_texture_id(0U) {}
        texture_handle(gl_texture_id texture_id) : m_texture_id(texture_id) {}
        texture_handle(std::nullptr_t) : m_texture_id(0U) {}
        operator int() {return m_texture_id;}
        operator gl_texture_id() {return m_texture_id;}
        bool operator ==(const texture_handle &other) const {return m_texture_id == other.m_texture_id;}
        bool operator !=(const texture_handle &other) const {return m_texture_id != other.m_texture_id;}
        bool operator ==(std::nullptr_t) const {return m_texture_id == 0U;}
        bool operator !=(std::nullptr_t) const {return m_texture_id != 0U;}

        gl_texture_id m_texture_id;
    };

    struct texture_deleter
    {
        typedef texture_handle pointer;

        texture_deleter(gl_driver driver) : m_driver(driver) {}

        template<class other> texture_deleter(const other&) {};

        void operator()(pointer p) const
        {
            m_driver.delete_texture(p);
        }

        gl_driver m_driver;
    };

    typedef std::unique_ptr<gl_texture_id, texture_deleter> unique_texture;
    typedef std::vector<unique_texture> texture_vector;

    unique_texture make_texture(const gl_driver& driver,
                                unsigned int width,
                                unsigned int height,
                                image_format format,
                                const unsigned char* data);

    //-----------------------------------------------------------------------------------------------
    // Buffers
    //-----------------------------------------------------------------------------------------------
    struct buffer_handle
    {
        buffer_handle() : m_buffer_id(0U) {}
        buffer_handle(gl_buffer_id buffer_id) : m_buffer_id(buffer_id) {}
        buffer_handle(std::nullptr_t) : m_buffer_id(0U) {}
        operator int() {return m_buffer_id;}
        operator gl_buffer_id() {return m_buffer_id;}
        bool operator ==(const buffer_handle &other) const {return m_buffer_id == other.m_buffer_id;}
        bool operator !=(const buffer_handle &other) const {return m_buffer_id != other.m_buffer_id;}
        bool operator ==(std::nullptr_t) const {return m_buffer_id == 0U;}
        bool operator !=(std::nullptr_t) const {return m_buffer_id != 0U;}

        gl_buffer_id m_buffer_id;
    };

    struct buffer_deleter
    {
        typedef buffer_handle pointer;

        buffer_deleter(gl_driver driver) : m_driver(driver) {}

        template<class other> buffer_deleter(const other&) {};

        void operator()(pointer p) const
        {
            m_driver.delete_buffer(p);
        }

        gl_driver m_driver;
    };

    typedef std::unique_ptr<gl_buffer_id, buffer_deleter> unique_buffer;
    typedef std::vector<unique_buffer> buffer_vector;

    unique_buffer make_3d_buffer(const gl_driver& driver, const std::vector<glm::vec3>& data);
    unique_buffer make_2d_buffer(const gl_driver& driver, const std::vector<glm::vec2>& data);
    unique_buffer make_index_buffer(const gl_driver& driver, const std::vector<unsigned short>& data);

    //-----------------------------------------------------------------------------------------------
    // Cubenaps
    //-----------------------------------------------------------------------------------------------
    struct cubemap_handle
    {
        cubemap_handle() : m_cubemap_id(0U) {}
        cubemap_handle(gl_cubemap_id cubemap_id) : m_cubemap_id(cubemap_id) {}
        cubemap_handle(std::nullptr_t) : m_cubemap_id(0U) {}
        operator int() {return m_cubemap_id;}
        operator gl_cubemap_id() {return m_cubemap_id;}
        bool operator ==(const cubemap_handle &other) const {return m_cubemap_id == other.m_cubemap_id;}
        bool operator !=(const cubemap_handle &other) const {return m_cubemap_id != other.m_cubemap_id;}
        bool operator ==(std::nullptr_t) const {return m_cubemap_id == 0U;}
        bool operator !=(std::nullptr_t) const {return m_cubemap_id != 0U;}

        gl_cubemap_id m_cubemap_id;
    };

    struct cubemap_deleter
    {
        typedef cubemap_handle pointer;

        cubemap_deleter(gl_driver driver) : m_driver(driver) {}

        template<class other> cubemap_deleter(const other&) {};

        void operator()(pointer p) const
        {
            m_driver.delete_cubemap(p);
        }

        gl_driver m_driver;
    };

    typedef std::unique_ptr<gl_cubemap_id, cubemap_deleter> unique_cubemap;
    typedef std::vector<unique_cubemap> cubemap_vector;

    unique_cubemap make_cubemap(const gl_driver& driver,
                                unsigned int width,
                                unsigned int height,
                                image_format format,
                                const std::vector<const unsigned char*>& faces_data);

    //-----------------------------------------------------------------------------------------------
    // Programs
    //-----------------------------------------------------------------------------------------------
    struct program_handle
    {
        program_handle() : m_program_id(0U) {}
        program_handle(gl_program_id program_id) : m_program_id(program_id) {}
        program_handle(std::nullptr_t) : m_program_id(0U) {}
        operator int() {return m_program_id;}
        operator gl_program_id() {return m_program_id;}
        bool operator ==(const program_handle &other) const {return m_program_id == other.m_program_id;}
        bool operator !=(const program_handle &other) const {return m_program_id != other.m_program_id;}
        bool operator ==(std::nullptr_t) const {return m_program_id == 0U;}
        bool operator !=(std::nullptr_t) const {return m_program_id != 0U;}

        gl_program_id m_program_id;
    };

    struct program_deleter
    {
        typedef program_handle pointer;

        program_deleter(gl_driver driver) : m_driver(driver) {}

        template<class other> program_deleter(const other&) {};

        void operator()(pointer p) const
        {
            m_driver.delete_program(p);
        }

        gl_driver m_driver;
    };

    typedef std::unique_ptr<gl_program_id, program_deleter> unique_program;
    typedef std::vector<unique_program> program_vector;

    unique_program make_program(const gl_driver& driver,
                                program_type type);
} // namespace cgs

#endif // GL_DRIVER_UTIL_HPP