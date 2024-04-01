target_sources( ${PROJECT_NAME} 
    PRIVATE
        application.cpp
        application.h
        main.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)