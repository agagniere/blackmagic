##
 # Makefile for Sphinx documentation
 # Automatically compile and execute code samples to keep the documentation up to date
 # Handle a virtual environment for python dependencies
##

# Input Folders
SourceFolder  := pages
SampleFolder  := samples
HeaderFolder  := ../include

# Input Files
Pages         := $(shell find $(SourceFolder) -type f \( -name '*.md' -o -name '*.rst' \))
Pages         += ../README.md
SourceCode    := $(shell find $(SampleFolder) $(HeaderFolder) -type f -name '*.[ch]')

# Generated Folders
SphinxFolder  := sphinx
DoxygenFolder := doxygen
PreproFolder  := preprocessed
ExecFolder    := cache
OutputFolder  := outputs
VenvFolder    := .env

# Generated Files
DoxygenHtml   := $(DoxygenFolder)/html/index.html
DoxygenXml    := $(DoxygenFolder)/xml/index.xml
SphinxMan     := $(SphinxFolder)/man/blackmagic.1
SphinxHtml    := $(SphinxFolder)/html/index.html
SphinxPdf     := $(SphinxFolder)/latexpdf/blackmagic.pdf

# Samples are small programs whose output we want to include in the documentation
Samples          := $(wildcard $(SampleFolder)/*.c)
ProcessedSamples := $(Samples:$(SampleFolder)/%.c=$(PreproFolder)/%.i)
Executables      := $(Samples:$(SampleFolder)/%.c=$(ExecFolder)/%.exe)
Outputs          := $(Samples:$(SampleFolder)/%.c=$(OutputFolder)/%.txt)

CPPFLAGS    += -I $(HeaderFolder)

Open        ?= open
ClangFormat ?= clang-format

SphinxOptions ?= -c . -n
Sphinx        ?= sphinx-build

VenvName     := sphinx
VenvActivate := $(VenvFolder)/bin/activate

Version ?= $(shell git tag --sort '-version:refname' --merged | head -1)

# When rendering the help, pretty print certain words
Cyan       := \033[36m
Bold       := \033[1m
EOC        := \033[0m
PP_command := $(Cyan)
PP_section := $(Bold)

.ONESHELL: # Keep the environment across lines

##@ General

default: help ## When no target is provided, display the help

help: ## Display this help.
	@awk 'BEGIN {FS = ":.*##"; printf "\nThis Makefile allows one to build the documentation of this project.\n\nUsage:\n  make $(PP_command)<target>$(EOC)\n"} /^[a-zA-Z_0-9-]+:.*?##/ { printf "  $(PP_command)%-15s$(EOC) %s\n", $$1, $$2 } /^##@/ { printf "\n$(PP_section)%s$(EOC):\n", substr($$0, 5) }' $(MAKEFILE_LIST)

raw_help: ## Display the help without color
	@$(MAKE) help --no-print-directory PP_command= PP_section= EOC=

.PHONY: default help raw_help

##@ Generate documentation

doxygen_html: $(DoxygenHtml) ## Generate and open a techical documentation website

html: $(SphinxHtml) ## Generate and open a high-level documentation website

man: $(SphinxMan) ## Generate and open the documentation in the terminal
	man $<

pdf: $(SphinxPdf) ## Generate and open the documentation as a PDF
	$(Open) $(SphinxFolder)/latex/blackmagic.pdf

doxygen_html html:
	$(Open) $< 2>/dev/null

.PHONY: doxygen_html html man pdf

##@ Remove generated files

clean: ## Remove the compiled samples and their outputs
	$(RM) -r $(OutputFolder) $(ExecFolder) $(PreproFolder)

doc_clean: clean ## Remove all generated documentation
	$(RM) -r $(SphinxFolder) $(DoxygenFolder)

full_clean: doc_clean ## Remove all generated files, including python local environment
	$(RM) -r $(VenvFolder)

.PHONY: clean doc_clean full_clean

##@ Misc

env: $(VenvActivate) ## Install the python virtual environment with dependencies

# Non phony rules

$(DoxygenHtml) $(DoxygenXml) &: Doxyfile.cfg $(SourceCode) Makefile
	PROJECT_VERSION=$(Version) OUTPUT_DIRECTORY=$(DoxygenFolder) INPUT=$(HeaderFolder) doxygen $<

# Preprocess samples
$(ProcessedSamples): $(PreproFolder)/%.i: $(SampleFolder)/%.c | $(PreproFolder)
	temp="$(@D)/_raw_$(@F)" ; \
	$(CC) -E $(CPPFLAGS) -CC $< -o "$$temp" ; \
	discard=$$(grep -E "^[#].*?$(<F)" "$$temp" -n | cut -d':' -f1 | tail -1) ; \
	tail +$$(( $$discard + 1 )) "$$temp" | $(ClangFormat) > $@

# Compile code samples
$(Executables): $(ExecFolder)/%.exe: $(SampleFolder)/%.c | $(ExecFolder)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

# Execute them
$(Outputs): $(OutputFolder)/%.txt: $(ExecFolder)/%.exe | $(OutputFolder)
	-./$< > $@

# Create folders for generated files
$(ExecFolder) $(OutputFolder) $(PreproFolder):
	mkdir -p $@

# Create a virtual environment with dependencies
$(VenvActivate): requirements.txt
	test -d $(VenvFolder) || python3 -m venv --prompt $(VenvName) --upgrade-deps $(VenvFolder)
	. $@
	pip install --requirement $<

# Run sphinx to generate documentation
$(SphinxPdf) $(SphinxMan) $(SphinxHtml): $(SphinxFolder)/%: $(Pages) $(SourceCode) $(ProcessedSamples) $(Outputs) $(DoxygenXml) Makefile conf.py | $(VenvActivate)
	test -z "$(VIRTUAL_ENV)" && . $|
	PROJECT_VERSION=$(Version) $(Sphinx) -M $(*D) "$(SourceFolder)" "$(SphinxFolder)" $(SphinxOptions) $(O)
