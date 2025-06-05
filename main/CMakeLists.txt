set(srcs "main.c" "nimble_spp_server.c" "cdc_acm_vcp.cpp")

idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "." REQUIRED_IDF_TARGETS esp32s3)
