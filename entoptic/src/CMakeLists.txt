add_executable(entoptic app.cc)
target_link_libraries(entoptic ${raspicam_CV_LIBS} oscpack ${OpenCV_LIBS})
