#include <nanobind/nanobind.h>
#include <greeter/Module1/Modul1.h>
#include <greeter/Module2/Modul1.h>
#include <greeter/Module3/Modul3.h>

namespace nb = nanobind;

NB_MODULE(_core, m) {
    m.def("get_info_m1", &greeter::module1::get_info);
    m.def("get_info_m2", &greeter::module2::get_info);
    m.def("sapa_m3", &greeter::module3::sapa);
}
