#!/bin/bash

BASE=$(dirname "$(readlink -f "$0")")
ROOT=$(dirname "${BASE}")

ARGS="--strictness-level 5 --validate-in-process --validate"
CONFIG=Release
INPUT=${ROOT}
OUTPUT=${ROOT}/build

ARTEFACTS=${OUTPUT}/VintageKnackBass_artefacts/${CONFIG}
PLUGINVAL=${OUTPUT}/_deps/pluginval-src/pluginval

# If specified, avoids tests that create GUI windows,
# which can cause problems on headless CI systems.
# https://github.com/Tracktion/pluginval/blob/develop/docs/Command%20line%20options.md
export SKIP_GUI_TESTS=1

# Execute pluginval.
"${PLUGINVAL}" ${ARGS} "${ARTEFACTS}/VST3/VintageKnackBass.vst3" || exit $?

# Delete intermediate files.
rm -fv "${ARTEFACTS}/libVintageKnackBass_SharedCode.a" || exit $?

# Zip binaries to preserve file permissions during artifact upload.
# https://github.com/actions/upload-artifact/issues/38
# https://github.com/actions/upload-artifact#permission-loss
pushd "${ARTEFACTS}"
zip -rm VintageKnackBass.zip . || exit $?
popd
