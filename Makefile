# Makefile for compiling Friso out of source directory
# @Author	chenxin<chenxin619315@gmail.com>

# Targets start here.
all testing static share install clean:
	cd src && $(MAKE) $@

# echo config parameters
echo:
	@echo "INSTALL_TOP= $(INSTALL_TOP)"
	@echo "INSTALL_BIN= $(INSTALL_BIN)"
	@echo "INSTALL_INC= $(INSTALL_INC)"
	@echo "INSTALL_LIB= $(INSTALL_LIB)"
	@echo "INSTALL_EXEC= $(INSTALL_EXEC)"
	@echo "INSTALL_DATA= $(INSTALL_DATA)"

# list targets that do not create files (but not all makes understand .PHONY)
.PHONY: all clean echo

# (end of Makefile)
