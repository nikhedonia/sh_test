# sh_test

Test fails as the working directory == project directory when executing `buck test :test`.


This is the generated `buck-out/gen/__test_runner__/test-runner.sh` script by `sh_binary`:
```bash
#!/bin/bash
# Run with -e so the script will fail if any of the steps fail.
set -e

SCRIPT_TO_RUN=buck-out/gen/main

# This script can be cached and used on machines other than the one where it was created. That
# means it can't contain any absolute filepaths. Expose the absolute filepath of the root of
# the project as $BUCK_REAL_ROOT, determined at runtime.
BUCK_REAL_ROOT="$(cd `dirname $0`; pwd)"
BUCK_TMP_ROOT="`mktemp -d -t sh_binary.XXXXXXXXXX`"
trap "rm -rf $BUCK_TMP_ROOT" EXIT HUP INT TERM

# Setup the symlinks in a subshell to avoid modifying state (e.g. chdir).
(
  cd "$BUCK_TMP_ROOT"

  # Create symlink to the cells in the folder containing this script.
  CELLS_NAMES=(
    __default__

  )
  CELLS_PATHS=(
    ../../..

  )

  # The following operation needs to be atomic.
  if [ ! -d "$BUCK_REAL_ROOT/cells/" ] ; then
    tmpfolder="`mktemp -d "$BUCK_REAL_ROOT/tmp.XXXXXXXXXX"`"
    for idx in "${!CELLS_NAMES[@]}"; do
      name="${CELLS_NAMES[$idx]}"
      path="${CELLS_PATHS[$idx]}"
      ln -sf "../$path" "$tmpfolder/$name"
    done
    mv -n "$tmpfolder/" "$BUCK_REAL_ROOT/cells/" 2>/dev/null || true
  fi

  # Symlink the resources to the $BUCK_TMP_ROOT directory.
  SYMLINK_PATHS=(
    __default__/buck-out/gen/res

    "__default__/$SCRIPT_TO_RUN"
  )

  for path in "${SYMLINK_PATHS[@]}"; do
    mkdir -p "$(dirname "$path")"
    ln -sf "$BUCK_REAL_ROOT/cells/$path" "$BUCK_TMP_ROOT/$path"
  done
)

BUCK_PROJECT_ROOT="$BUCK_TMP_ROOT/__default__" "$BUCK_TMP_ROOT/__default__/$SCRIPT_TO_RUN" "$@"
```

Note that the test passes if we force the working directory to match `dirname "$BUCK_TMP_ROOT/__default__/$SCRIPT_TO_RUN"`.

Simple way of verifying this is to manually edit this file by adding a `cd $BUCK_TMP_ROOT/__default__/buck-out/gen` just before the last line.
