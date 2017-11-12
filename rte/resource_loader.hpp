#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP

#include "resource_database.hpp"

#include <cstddef> // for size_t
#include <vector>
#include <string>

namespace cgs
{
    //-----------------------------------------------------------------------------------------------
    //! @brief Loads resources from a file (materials, meshes and resource nodes).
    //! @param file_name Path to the file to load from relative to the current directory.
    //! @param materials out Address of a pointer in which to store the address of an internal
    //!  array containing the ids of the materials which were created from the file. The contents
    //!  of this internal array will remain valid until the next call to this function.
    //!  Can't ne nullptr.
    //! @param num_materials_out Address of a variable in which to store the number of materials
    //!  which were created from the file. Can't be nullptr.
    //! @param meshes_out Address of a variable in which to store the address of an internal
    //!  array containing the ids of the meshes which were created from the file. The contents
    //!  of this internal array will remain valid until the next call to this function.
    //!  Can't be nullptr.
    //! @param num_meshes_out Address of a variable in which to store the number of meshes
    //!  which were created from the file. Can't be nullptr.
    //! @return The id of the root resource created from the file.
    //-----------------------------------------------------------------------------------------------
    void load_resources(const std::string& file_name,
                       resource_id* root_out,
                       resource_vector* resources_out,
                       material_vector* materials_out,
                       mesh_vector* meshes_out);
} // namespace cgs

#endif // RESOURCE_LOADER_HPP