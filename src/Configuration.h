#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Rincludes.h"
#include "utilities.h"
#include <sstream>
#include <unordered_map>

class Configuration {
  public:
    explicit Configuration(SEXP const evals, SEXP const raw_analysis_dirpath,
                           SEXP const analysis_flags, SEXP verbose)
        : evals_{rlist_to_map<SEXP>(evals, identity<SEXP>)},
          raw_analysis_dirpath_{rvector_to_string(raw_analysis_dirpath)},
          verbose_{rvector_to_bool(verbose)},
          enable_jit_{read_environment_variable("R_ENABLE_JIT")},
          compile_pkgs_{read_environment_variable("R_COMPILE_PKGS")},
          disable_bytecode_{read_environment_variable("R_DISABLE_BYTECODE")},
          git_commit_info_{GIT_COMMIT_INFO} {
        std::unordered_map<std::string, bool> analysis_flags_{
            rlist_to_map<bool>(analysis_flags, rvector_to_bool)};
        eval_expression_analysis_enabled_ =
            analysis_flags_["eval_expression_analysis"];
    }

    const std::unordered_map<std::string, SEXP> get_evals() const {
        return evals_;
    }

    bool is_eval_expression_analysis_enabled() const {
        return eval_expression_analysis_enabled_;
    }

    bool is_execution_context_stack_needed() const {
        return eval_expression_analysis_enabled_;
    }

    const std::string &get_raw_analysis_dirpath() const {
        return raw_analysis_dirpath_;
    }

    bool is_verbose() const { return verbose_; }

    const std::string &get_enable_jit() const { return enable_jit_; }

    const std::string &get_compile_pkgs() const { return compile_pkgs_; }

    const std::string &get_disable_bytecode() const {
        return disable_bytecode_;
    }

    const std::string &get_git_commit_info() const { return git_commit_info_; }

    explicit operator std::string() const {
        std::stringstream rep;
        rep << "Configuration : " << std::endl;
        rep << "- Eval Addresses : " << std::endl;
        for (auto &key_value : evals_) {
            rep << "    - " << key_value.first << " : " << key_value.second
                << std::endl;
        }
        rep << "- Analysis Flags : " << std::endl;
        rep << "    - Eval Expression Analysis : "
            << is_eval_expression_analysis_enabled() << std::endl;
        rep << "- Raw analysis directory path : " << get_raw_analysis_dirpath()
            << std::endl;
        rep << "- Verbose                     : " << is_verbose() << std::endl;
        rep << "- Git Commit Information      : " << get_git_commit_info()
            << std::endl;
        rep << "- Environment Variables : " << std::endl;
        rep << "    - R_ENABLE_JIT            : " << get_enable_jit()
            << std::endl;
        rep << "    - R_COMPILE_PKGS          : " << get_compile_pkgs()
            << std::endl;
        rep << "    - R_DISABLE_BYTECODE      : " << get_disable_bytecode()
            << std::endl;

        return rep.str();
    }

  private:
    std::unordered_map<std::string, SEXP> evals_;
    std::string raw_analysis_dirpath_;
    bool verbose_;
    bool eval_expression_analysis_enabled_;
    std::string enable_jit_;
    std::string compile_pkgs_;
    std::string disable_bytecode_;
    std::string git_commit_info_;
};

#endif /* __CONFIGURATION_H__ */
