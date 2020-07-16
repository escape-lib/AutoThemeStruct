#include "common.hpp"
#include "messages/messages.hpp"

#include <filesystem>
#include <fstream>

#define MIN_ARGC 2
#define PARENT_DIR_ARGC 3

namespace fs = std::filesystem;

bool FileDirectoryExists(const std::string& path) {
    fs::path obj(path);
    return fs::exists(obj);
}

/*std::string::find is an alternative*/
bool IllegalCharCheck(const std::string& target, const std::string& char_set) {
    for (char d : char_set) {
        for (char t : target) {
            if (t == d) { return true; }
        }
    }

    return false;
}

const std::string base_plist = R"(<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
  <dict>
       <key>IB-MaskIcons</key>
    <true/>
    <key>ExamplePackageName</key>
    <string>ExampleThemeName</string>
    <key>ExampleThemeType</key>
    <string>Icons</string>
    </dict>
  </plist>)";

inline void ReplaceString(std::string& target, const std::string& from, const std::string& to) {
    size_t pos = 0;
    while ((pos = target.find(from, pos)) != std::string::npos) {
        target.replace(pos, from.length(), to);
        pos += to.length();
    }
}

inline void GetLastStrDelim(std::string& copy_str, const std::string str_read, const char delim) {
    size_t last_delim_pos = str_read.find_last_of(delim) + 1;
    copy_str = str_read.substr(last_delim_pos, str_read.length() - last_delim_pos);
}

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false); /*no need for sync with all iostream std */

    if (argc < MIN_ARGC) {
        usage::PrintUsage();
        return -1;
    }
    
    const std::string theme_name = argv[1];

    std::string parent_dir = argc >= PARENT_DIR_ARGC ? argv[2] : "";
    bool using_parent_dir = parent_dir != "";

    if (using_parent_dir) { std::replace(parent_dir.begin(), parent_dir.end(), '\\', '/'); } //win32 directory split char

    if (parent_dir.back() != '/') {
        parent_dir.push_back('/');
    }

    const std::string theme_dir_name = theme_name + ".theme";
    
    if (IllegalCharCheck(theme_name, disallowed_characters_)) {
        std::cerr << illegal_char_prefix << "theme name" << illegal_char_suffix;
        return -1;

    }

    if (using_parent_dir) {
        if (!FileDirectoryExists(parent_dir)) {
            std::cerr << parent_dir_noexist;
            return -1;

        }
        else if (FileDirectoryExists(parent_dir + theme_dir_name)) {
            std::cerr << theme_dir_exists;
            return -1;
        }
    }
    else if (FileDirectoryExists(theme_dir_name)) {
        std::cerr << theme_dir_exists;
        return -1;
    }

    const std::string dir_struct_a = theme_dir_name + "/IconBundles";
    const std::string dir_struct_b = theme_dir_name + "/Bundles/com.apple.mobileicons.framework";

    const bool struct_a_status = fs::create_directories(using_parent_dir ? parent_dir + dir_struct_a : dir_struct_a);
    const bool struct_b_status = fs::create_directories(using_parent_dir ? parent_dir + dir_struct_b : dir_struct_b);

    if (!struct_a_status
        || !struct_b_status) {

        std::cerr << error_create_dir_struct;
        return -1;
    }

    std::ofstream info(using_parent_dir ? parent_dir + theme_dir_name + "/Info.plist" : theme_dir_name + "/Info.plist");
    if (!info.is_open()) {
        std::cerr << error_create_file_prefix << "Info.plist" << error_create_file_suffix;
        std::cerr << parent_dir + theme_dir_name + "/Info.plist";
        return -1;
    }

    std::string plist_data = base_plist;

    ReplaceString(plist_data, "ExampleThemeName", theme_name);
    ReplaceString(plist_data, "ExamplePackageName", theme_name);

    info << plist_data;
    info.close();


    const std::string fsucess_parent = sucess_parent + theme_name + '\n';
    const std::string fsucess_no_parent = sucess_no_parent + theme_name + '\n';


    if (using_parent_dir) { std::cout << fsucess_parent; }
    else { std::cout << fsucess_no_parent; }

    return 0;
}