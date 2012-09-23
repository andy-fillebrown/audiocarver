
pydev_path = "/-/usr/bin/eclipse/plugins/org.python.pydev.debug_2.4.0.2012020116/pysrc"

import sys
if sys.path.count(pydev_path) < 1:
    sys.path.append(pydev_path)

import pydevd
pydevd.settrace(stdoutToServer=False, stderrToServer=False, suspend=False)
