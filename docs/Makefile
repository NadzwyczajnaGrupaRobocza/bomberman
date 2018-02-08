BASE_DIR := $(shell pwd)

PLANT_UML=plantuml

UML_DIR := $(BASE_DIR)/uml_src
SRCS := $(wildcard $(UML_DIR)/*.uml)

OUT_DIR := $(BASE_DIR)/img

DIAGS := $(addprefix $(OUT_DIR)/,$(notdir $(patsubst %.uml,%.png,$(SRCS))))

$(OUT_DIR)/%.png: $(UML_DIR)/%.uml
	${PLANT_UML} $< -o $(OUT_DIR)

all: $(DIAGS)
