#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

$(call inherit-product, device/xiaomi/davinci/device.mk)

# Inherit some common stuff.
TARGET_BOOT_ANIMATION_RES := 1080
$(call inherit-product, vendor/ion/config/common_full_phone.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_BRAND := Xiaomi
PRODUCT_DEVICE := davinci
PRODUCT_MANUFACTURER := Xiaomi
PRODUCT_NAME := ion_davinci

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

# Inherit from custom vendor
$(call inherit-product, vendor/MiuiCamera/config.mk)

PLATFORM_SECURITY_PATCH_OVERRIDE := 2020-01-01

BUILD_FINGERPRINT := "Xiaomi/davinci_eea/davinci:10/QKQ1.190825.002/V11.0.4.0.QFJEUXM:user/release-keys"

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="davinci-user 10 QKQ1.190825.002 V11.0.4.0.QFJEUXM release-keys" \
    PRODUCT_NAME="davinci" \
    TARGET_DEVICE="davinci"
