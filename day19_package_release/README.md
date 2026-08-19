# Day19: Package And Release

这个练习使用 vcpkg manifest 管理 `fmt` 和 `spdlog`，再用 CMake 完成构建、测试、安装和 ZIP 打包。

## 本地构建

先准备 vcpkg，并设置环境变量 `VCPKG_ROOT`。然后在项目目录执行：

```powershell
cmake -S . -B build -G Ninja `
  -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
cmake --install build --prefix package --config Release
```

也可以让 vcpkg 根据项目根目录的 `vcpkg.json` 恢复依赖：

```powershell
& "$env:VCPKG_ROOT/vcpkg.exe" install --triplet x64-windows
```

## 生成 ZIP

```powershell
cmake -E tar cfv day19-windows.zip --format=zip package
```

## 关键文件

- `vcpkg.json`: 项目依赖清单
- `CMakeLists.txt`: target、依赖、测试、安装和 CPack 配置
- `.github/workflows/ci.yml`: Windows/Linux/macOS 矩阵构建和 artifact 上传

Windows 默认使用 `x64-windows`，它通常需要动态运行库或依赖 DLL。若改用 `x64-windows-static`，必须让 CMake 配置和依赖安装使用同一个 triplet。
