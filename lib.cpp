#include "MaestroControl.hpp"
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE (libMaestroControl) {
    class_<MaestroControl>("MaestroControl", init<const char *>())
            .def("SetTarget", &MaestroControl::SetTarget)
            .def("GetPosition", &MaestroControl::GetPosition)
            .def("toString", &MaestroControl::toString)
            .def("reconnect", &MaestroControl::reconnect)
            .def("destroy", &MaestroControl::destroy);
};
