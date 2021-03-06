cmake_minimum_required(VERSION 3.5)
set(QT_MIN_VERSION "5.4.0")
set(KF5_MIN_VERSION "5.16.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(
    CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH}
        ${ECM_KDE_MODULE_DIR}
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(FeatureSummary)
add_library(kio_hello MODULE hello.cpp)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED KIO)
target_link_libraries(kio_hello KF5::KIOCore)
set_target_properties(kio_hello PROPERTIES OUTPUT_NAME "hello")

install(TARGETS kio_hello DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/kio )
