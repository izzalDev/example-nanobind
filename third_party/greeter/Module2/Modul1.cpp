#include "Modul1.h"
#include <fmt/core.h>
namespace greeter::module2 {
    std::string get_info() { return fmt::format("Pesan dari Module {} via fmt", 2); }
}
