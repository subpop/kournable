set(kournable_SRC
    kournable.cpp
    main.cpp
    mainwindow.cpp
)

add_executable(kournable ${kournable_SRC})

target_link_libraries(kournable
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    KF5::WidgetsAddons
    KF5::KIOCore
)

# Install the executable
install(TARGETS kournable ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES kournableui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kournable)
