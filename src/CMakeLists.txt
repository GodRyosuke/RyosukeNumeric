# 実行ファイル生成に関する情報
add_library(
	Mat3
	Mat3.cpp
)
# target_link_libraries(WanderLibTests PRIVATE wander-lib)
target_include_directories(Mat3 PUBLIC "${PROJECT_SOURCE_DIR}/include")