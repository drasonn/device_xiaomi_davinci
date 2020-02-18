/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include "property_service.h"
#include "vendor_init.h"

using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_triple(char const product_prop[], char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(product_prop, value);
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void load_davinciglobal() {
    property_override("ro.product.model", "Mi 9T");
    property_override("ro.build.product", "davinci");
    property_override("ro.product.device", "davinci");
    property_override("ro.build.description", "davinci-user 10 QKQ1.190825.002 V11.0.4.0.QFJEUXM release-keys");
}

void load_davinciin() {
    property_override("ro.product.model", "Redmi K20");
    property_override("ro.build.product", "davinciin");
    property_override("ro.product.device", "davinciin");
    property_override("ro.build.description", "davinciin-user 10 QKQ1.190825.002 V11.0.1.0.QFJINXM release-keys");
}

void load_davinci() {
    property_override("ro.product.model", "Redmi K20");
    property_override("ro.build.product", "davinci");
    property_override("ro.product.device", "davinci");
    property_override("ro.build.description", "davinci-user 10 QKQ1.190825.002 V11.0.2.0.QFJCNXM release-keys");
}

void load_dalvikvm_properties()
{
    struct sysinfo sys;

    sysinfo(&sys);
    if (sys.totalram < 7000ull * 1024 * 1024) {
        // 4/6GB RAM
        property_override("dalvik.vm.heapstartsize", "16m");
        property_override("dalvik.vm.heaptargetutilization", "0.5");
        property_override("dalvik.vm.heapmaxfree", "32m");
    } else {
        // 8/12/16GB RAM
        property_override("dalvik.vm.heapstartsize", "24m");
        property_override("dalvik.vm.heaptargetutilization", "0.46");
        property_override("dalvik.vm.heapmaxfree", "48m");
    }

    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heapsize", "512m");
    property_override("dalvik.vm.heapminfree", "8m");
}

void vendor_load_properties() {
    std::string region = android::base::GetProperty("ro.boot.hwc", "");

    if (region.find("CN") != std::string::npos) {
        load_davinci();
    } else if (region.find("INDIA") != std::string::npos) {
        load_davinciin();
    } else {
        load_davinciglobal();
    }

    property_override("ro.oem_unlock_supported", "0");
    property_override("ro.control_privapp_permissions", "log");
    property_override_triple("ro.build.fingerprint", "ro.system.build.fingerprint", "ro.vendor.build.fingerprint", "google/coral/coral:10/QQ1B.200205.002/6084387:user/release-keys");

    load_dalvikvm_properties();
}
