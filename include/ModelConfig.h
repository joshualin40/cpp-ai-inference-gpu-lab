#ifndef MODEL_CONFIG_H
#define MODEL_CONFIG_H

#include <string> 
#include <filesystem> 

namespace workbench {
    struct ModelConfig {
        std::string model_name;
        std::filesystem::path model_path;
        size_t context_size{2048}; 
    };

    struct GenerationConfig {
        size_t max_new_tokens{128}; 
        double temperature{0.7}; 
        double top_p{0.9}; 
    }; 

    struct InferenceRequest {
        std::string prompt; 
        GenerationConfig generation_config; 
    }; 

    struct InferenceResponse {
        std::string generated_text; 
        size_t prompt_tokens{0}; 
        size_t generated_tokens{0}; 
    }; 
}
#endif