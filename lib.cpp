#include "MaestroControl.hpp"
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE (libMaestroControl) {
    class_<MaestroControl>("MaestroControl", init<const char *>())
            .def("setPosition", &MaestroControl::setPosition)
            .def("getPosition", &MaestroControl::getPosition)
            .def("getSerialPort", &MaestroControl::getSerialPort)
            .def("reconnect", &MaestroControl::reconnect)
            .def("destroy", &MaestroControl::destroy);
};
