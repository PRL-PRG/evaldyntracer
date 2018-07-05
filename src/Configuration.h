#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Rincludes.h"
#include "utilities.h"
#include <sstream>
#include <unordered_map>

using eval_t = std::pair<std::string, SEXP>;

inline std::string get_eval_name(const eval_t &eval) { return eval.first; }

inline SEXP get_eval_function(const eval_t &eval) { return eval.second; }

class Configuration {
  public:
    explicit Configuration(SEXP const evals, SEXP const raw_analysis_dirpath,
                           SEXP const analysis_flags, SEXP verbose)
        : raw_analysis_dirpath_{rvector_to_string(raw_analysis_dirpath)},
          verbose_{rvector_to_bool(verbose)},
          enable_jit_{read_environment_variable("R_ENABLE_JIT")},
          compile_pkgs_{read_environment_variable("R_COMPILE_PKGS")},
          disable_bytecode_{read_environment_variable("R_DISABLE_BYTECODE")},
          git_commit_info_{GIT_COMMIT_INFO} {

        transform_rlist(evals, [&](std::string name, SEXP function) {
            evals_.push_back({name, function});
        });
        std::unordered_map<std::string, bool> analysis_flags_{
            rlist_to_map<bool>(analysis_flags, rvector_to_bool)};
        eval_expression_analysis_enabled_ =
            analysis_flags_["eval_expression_analysis"];
    }

    const std::optional<eval_t> get_eval_type(const SEXP function) const {
        for (const auto &eval : evals_) {
            if (eval.second == function) {
                return eval;
            }
        }
        return {};
    }

    bool is_eval_expression_analysis_enabled() const {
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
    std::vector<eval_t> evals_;
    std::string raw_analysis_dirpath_;
    bool verbose_;
    bool eval_expression_analysis_enabled_;
    std::string enable_jit_;
    std::string compile_pkgs_;
    std::string disable_bytecode_;
    std::string git_commit_info_;
};

#endif /* __CONFIGURATION_H__ */
