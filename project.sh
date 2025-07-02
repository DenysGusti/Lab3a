#!/bin/bash
set -e

BUILD_TYPE="Release"
BUILD_DIR="build-release"
EXECUTABLE="Lab3a"

function usage() {
    echo "Usage: ./project.sh <command> [options]"
    echo ""
    echo "Commands:"
    echo "  configure [--debug|--release]     Configure the project"
    echo "  build     [--debug|--release]     Build the project"
    echo "  run       [--debug|--release] <args...>   Run the executable with arguments"
    echo "  clean                             Remove build directories"
    echo ""
}

function parse_build_type() {
    if [[ "$1" == "--debug" ]]; then
        BUILD_TYPE="Debug"
        BUILD_DIR="build-debug"
        shift
        echo "$@"
    elif [[ "$1" == "--release" ]]; then
        BUILD_TYPE="Release"
        BUILD_DIR="build-release"
        shift
        echo "$@"
    else
        # no build type flag, keep defaults
        echo "$@"
    fi
}

case "$1" in
    configure)
        shift
        if parse_build_type "$1"; then
            shift
        fi
        echo "Configuring project ($BUILD_TYPE)..."
        cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
        ;;

    build)
        shift
        if parse_build_type "$1"; then
            shift
        fi
        echo "Building project ($BUILD_TYPE)..."
        cmake --build "$BUILD_DIR" --target "$EXECUTABLE" -j "$(nproc)"
        ;;

    run)
        shift
        if parse_build_type "$1"; then
            shift
        fi
        if [[ ! -f "$BUILD_DIR/$EXECUTABLE" ]]; then
            echo "Executable not found. Try: ./project.sh build [--debug|--release]"
            exit 1
        fi
        # shellcheck disable=SC2145
        echo "Running $EXECUTABLE ($BUILD_TYPE) with args: $@"
        (
            cd "$BUILD_DIR"
            echo "cwd: $(pwd)"
            echo "exec: ./$EXECUTABLE $*"
            ./"$EXECUTABLE" "$@"
        )
        ;;

    clean)
        echo "Cleaning build directories..."
        rm -rf build-debug build-release
        ;;

    *)
        usage
        ;;
esac
