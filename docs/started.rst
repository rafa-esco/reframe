===============
Getting Started
===============

Requirements
------------

* Python 3.5 or higher. Python 2 is not supported.

.. note::
  .. versionchanged:: 2.8
    A functional TCL modules system is no more required. ReFrame can now operate without a modules system at all.

Optional
~~~~~~~~

* For running the unit tests of the framework, the `pytest <https://pytest.org/>`__ unittesting framework is needed.

You are advised to run the `unit tests <#running-the-unit-tests>`__ of the framework after installing it on a new system to make sure that everything works fine.

.. note::
  .. versionchanged:: 2.12
    Migration to the `pytest <https://pytest.org/>`__ unittesting framework.

Getting the Framework
---------------------

To get the latest stable version of the framework, you can just clone it from the `github <https://github.com/eth-cscs/reframe>`__ project page:

.. code:: bash

    git clone https://github.com/eth-cscs/reframe.git

Alternatively, you can pick a previous stable version by downloading it from the previous `releases <https://github.com/eth-cscs/reframe/releases>`__ section.

Running the Unit Tests
----------------------

After you have downloaded the framework, it is important to run the unit tests of to make sure that everything is set up correctly:

.. code:: bash

    ./test_reframe.py -v

The output should look like the following:

.. code:: bash

  unittests/test_cli.py::TestFrontend::test_check_failure PASSED                         [  0%]
  unittests/test_cli.py::TestFrontend::test_check_sanity_failure PASSED                  [  1%]
  unittests/test_cli.py::TestFrontend::test_check_setup_failure PASSED                   [  1%]
  unittests/test_cli.py::TestFrontend::test_check_submit_success SKIPPED                 [  1%]
  unittests/test_cli.py::TestFrontend::test_check_success PASSED                         [  1%]
  unittests/test_cli.py::TestFrontend::test_checkpath_recursion PASSED                   [  2%]
  unittests/test_cli.py::TestFrontend::test_execution_modes PASSED                       [  2%]
    .
    .
    .
  unittests/test_utility.py::TestImportFromFile::test_load_relpath PASSED                [ 98%]
  unittests/test_utility.py::TestImportFromFile::test_load_unknown_path PASSED           [ 98%]
  unittests/test_utility.py::TestDebugRepr::test_builtin_types PASSED                    [ 99%]
  unittests/test_utility.py::TestDebugRepr::test_obj_repr PASSED                         [ 99%]
  unittests/test_utility.py::TestChangeDirCtxManager::test_change_dir_working PASSED     [ 99%]
  unittests/test_utility.py::TestChangeDirCtxManager::test_exception_propagation PASSED  [100%]

  =========================== 366 passed, 21 skipped in 29.16 seconds ==========================

You will notice in the output that all the job submission related tests have been skipped.
The test suite detects if the current system has a job submission system and is configured for ReFrame (see `Configuring ReFrame for your site <configure.html>`__) and it will skip all the unsupported unit tests.
As soon as you configure ReFrame for your system, you can rerun the test suite to check that job submission unit tests pass as well.
Note here that some unit tests may still be skipped depending on the configured job submission system.

Where to Go from Here
---------------------

The next step from here is to setup and configure ReFrame for your site, so that ReFrame can automatically recognize it and submit jobs.
Please refer to the `"Configuring ReFrame For Your Site" <configure.html>`__ section on how to do that.

Before starting implementing a regression test, you should go through the `"The Regression Test Pipeline" <pipeline.html>`__ section, so as to understand the mechanism that ReFrame uses to run the regression tests.
This section will let you follow easily the `"ReFrame Tutorial" <tutorial.html>`__ as well as understand the more advanced examples in the `"Customizing Further A Regression Test" <advanced.html>`__ section.

To learn how to invoke the ReFrame command-line interface for running your tests, please refer to the `"Running ReFrame" <running.html>`__ section.
