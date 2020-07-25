/* Copyright © 2019 escape-lib. All rights reserved.*/

#pragma once
#include "..\common.hpp"

/*_ suffix marking as raw*/
const std::string disallowed_characters_ = R"(\/:*?"<>|)";

const std::string theme_dir_exists = "Theme directory already exists!\n";
const std::string parent_dir_noexist = "Parent directory does not exist!\n";

const std::string illegal_char_prefix = "Illegal characters in ";
const std::string illegal_char_suffix = "! The following characters are disallowed: " + disallowed_characters_ + '\n';

const std::string error_create_file_prefix = "Could not create file ";
const std::string error_create_file_suffix = "! Do you have write permissions?\n";

const std::string error_create_dir_struct = "Could not create directory structure! Do you have write permissions?\n";

const std::string success_suffix = " - Created theme struct with name: ";

const std::string sucess_no_parent = "Success! sw[NO_PARENT]" + success_suffix;
const std::string sucess_parent = "Success! sw[PARENT]" + success_suffix;
