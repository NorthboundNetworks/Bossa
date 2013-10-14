///////////////////////////////////////////////////////////////////////////////
// BOSSA
//
// Copyright (C) 2011-2012 ShumaTech http://www.shumatech.com/
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////////////
#include "LinuxPortFactory.h"
#include "PosixSerialPort.h"

#include <string.h>
#include <stdio.h>

#include <string>

LinuxPortFactory::LinuxPortFactory()
{
    _dir = opendir("/dev");
}

LinuxPortFactory::~LinuxPortFactory()
{
    if (_dir)
        closedir(_dir);
}

SerialPort::Ptr
LinuxPortFactory::create(const std::string& name)
{
    bool isUsb = false;

    if (name.find("ttyUSB") != std::string::npos ||
        name.find("ttyACM") != std::string::npos)
        isUsb = true;

    return SerialPort::Ptr(new PosixSerialPort(name, isUsb));
}

std::string
LinuxPortFactory::begin()
{
    if (!_dir)
        return end();

    rewinddir(_dir);

    return next();
}

std::string
LinuxPortFactory::next()
{
    struct dirent* entry;

    if (!_dir)
        return end();

    while ((entry = readdir(_dir)))
    {
        if (strncmp("ttyUSB", entry->d_name, sizeof("ttyUSB") - 1) == 0)
            return std::string(entry->d_name);
        else if (strncmp("ttyACM", entry->d_name, sizeof("ttyACM") - 1) == 0)
            return std::string(entry->d_name);
        else if (strncmp("ttyS", entry->d_name, sizeof("ttyS") - 1) == 0)
            return std::string(entry->d_name);
    }

    return end();
}

std::string
LinuxPortFactory::end()
{
    return std::string();
}
