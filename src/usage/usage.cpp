#include "..\common.hpp"

namespace usage {
	void PrintUsage() {
		const std::string usage = "\nUsage: AutoThemeStruct <theme_name> <parent_directory>"
			"\nNote: Parent directory can be left blank to save the theme directory in the current directory (acting as parent).\n";

		std::cerr << usage;
	}
}