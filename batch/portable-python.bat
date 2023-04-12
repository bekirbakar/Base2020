ECHO ON

CMD /k %python_path% -m pip uninstall setuptools pip -y

SET python="interpreter\python.exe"
SET pip="interpreter\Scripts\pip.exe"

ECHO Uninstall Setuptools
%python% -m pip uninstall setuptools pip -y

ECHO Re-install Setuptools
%python% -m ensurepip --default-pip

ECHO Upgrade Pip
%python% -m pip install --upgrade pip

ECHO Install Packages

SET python="interpreter\python.exe"
SET pip="interpreter\Scripts\pip3.6.exe"

%pip% install --no-index --find-links="wheels\setuptools" setuptools==46.3.1

# Install a Package
%pip% install --no-index --find-links="wheels\bs4" tensorflow==2.1.0
