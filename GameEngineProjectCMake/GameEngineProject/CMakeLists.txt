# CMakeList.txt : CMake project for GameEngineProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (main "main.cc" "main.ih" "important/source.cc")
#include_directories("GameEngineProject/important")

# Create a debug build
set(CMAKE_CXX_FLAGS "-Wall --std=c++2a")
set(SFML_DIR SFML-2.5.1/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

#target_link_libraries(SFMLTest sfml-graphics sfml-audio)

# Set all CPP files to be source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
#file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} "SFML/Audio.hpp" "SFML/Config.hpp" "SFML/GpuPreference.hpp" "SFML/Graphics.hpp" "SFML/Main.hpp" "SFML/Network.hpp" "SFML/OpenGL.hpp" "SFML/System.hpp" "SFML/Window.hpp" "SFML/Audio/AlResource.hpp" "SFML/Audio/Export.hpp" "SFML/Audio/InputSoundFile.hpp" "SFML/Audio/Listener.hpp" "SFML/Audio/Music.hpp" "SFML/Audio/OutputSoundFile.hpp" "SFML/Audio/Sound.hpp" "SFML/Audio/SoundBuffer.hpp" "SFML/Audio/SoundBufferRecorder.hpp" "SFML/Audio/SoundFileFactory.hpp" "SFML/Audio/SoundFileReader.hpp" "SFML/Audio/SoundFileWriter.hpp" "SFML/Audio/SoundRecorder.hpp" "SFML/Audio/SoundSource.hpp" "SFML/Audio/SoundStream.hpp" "SFML/Graphics/BlendMode.hpp" "SFML/Graphics/CircleShape.hpp" "SFML/Graphics/Color.hpp" "SFML/Graphics/ConvexShape.hpp" "SFML/Graphics/Drawable.hpp" "SFML/Graphics/Export.hpp" "SFML/Graphics/Font.hpp" "SFML/Graphics/Glsl.hpp" "SFML/Graphics/Glyph.hpp" "SFML/Graphics/Image.hpp" "SFML/Graphics/PrimitiveType.hpp" "SFML/Graphics/Rect.hpp" "SFML/Graphics/RectangleShape.hpp" "SFML/Graphics/RenderStates.hpp" "SFML/Graphics/RenderTarget.hpp" "SFML/Graphics/RenderTexture.hpp" "SFML/Graphics/RenderWindow.hpp" "SFML/Graphics/Shader.hpp" "SFML/Graphics/Shape.hpp" "SFML/Graphics/Sprite.hpp" "SFML/Graphics/Text.hpp" "SFML/Graphics/Texture.hpp" "SFML/Graphics/Transform.hpp" "SFML/Graphics/Transformable.hpp" "SFML/Graphics/Vertex.hpp" "SFML/Graphics/VertexArray.hpp" "SFML/Graphics/VertexBuffer.hpp" "SFML/Graphics/View.hpp" "SFML/Network/Export.hpp" "SFML/Network/Ftp.hpp" "SFML/Network/Http.hpp" "SFML/Network/IpAddress.hpp" "SFML/Network/Packet.hpp" "SFML/Network/Socket.hpp" "SFML/Network/SocketHandle.hpp" "SFML/Network/SocketSelector.hpp" "SFML/Network/TcpListener.hpp" "SFML/Network/TcpSocket.hpp" "SFML/Network/UdpSocket.hpp" "SFML/System/Clock.hpp" "SFML/System/Err.hpp" "SFML/System/Export.hpp" "SFML/System/FileInputStream.hpp" "SFML/System/InputStream.hpp" "SFML/System/Lock.hpp" "SFML/System/MemoryInputStream.hpp" "SFML/System/Mutex.hpp" "SFML/System/NativeActivity.hpp" "SFML/System/NonCopyable.hpp" "SFML/System/Sleep.hpp" "SFML/System/String.hpp" "SFML/System/Thread.hpp" "SFML/System/ThreadLocal.hpp" "SFML/System/ThreadLocalPtr.hpp" "SFML/System/Time.hpp" "SFML/System/Utf.hpp" "SFML/System/Vector2.hpp" "SFML/System/Vector3.hpp" "SFML/Window/Clipboard.hpp" "SFML/Window/Context.hpp" "SFML/Window/ContextSettings.hpp" "SFML/Window/Cursor.hpp" "SFML/Window/Event.hpp" "SFML/Window/Export.hpp" "SFML/Window/GlResource.hpp" "SFML/Window/Joystick.hpp" "SFML/Window/Keyboard.hpp" "SFML/Window/Mouse.hpp" "SFML/Window/Sensor.hpp" "SFML/Window/Touch.hpp" "SFML/Window/VideoMode.hpp" "SFML/Window/Window.hpp" "SFML/Window/WindowHandle.hpp" "SFML/Window/WindowStyle.hpp")


# TODO: Add tests and install targets if needed.
install(TARGETS GameEngineProject DESTINATION "bin")

