locals {
  has_policies = var.tenant.iam_policies != null
  policies = local.has_policies ? var.tenant.iam_policies : {
    self         = null
    cross_tenant = null
    infra        = null
  }

  default_self_iam_policies = ["s3_datalake_space_rw"]
  lookup_self_iam_policies  = lookup(local.policies, "self_iam_policies", local.default_self_iam_policies)
  self_iam_policies         = local.lookup_self_iam_policies == null ? local.default_self_iam_policies : local.lookup_self_iam_policies

  default_cross_tenant_policies = {}
  lookup_cross_tenant_policies  = lookup(local.policies, "cross_tenant", local.default_cross_tenant_policies)
  cross_tenant_raw              = local.lookup_cross_tenant_policies == null ? local.default_cross_tenant_policies : local.lookup_cross_tenant_policies
  cross_tenant_policies = merge([
    for env, definition in local.cross_tenant_raw :
    env == "each" ?
    { for tenant_name, policies in definition :
      "${var.env}-${replace(tenant_name, "_", "-")}" => policies
    } :
    env == "all" ? definition :
    env == var.env ? definition : {}
  ]...)

  default_infra_policies = {}
  lookup_infra_policies  = lookup(local.policies, "infra", local.default_infra_policies)
  infra_policies_raw     = local.lookup_infra_policies == null ? local.default_infra_policies : local.lookup_infra_policies
  infra_policies = [for policy_name in distinct(flatten([
    for env, definition in local.infra_policies_raw :
    env == "each" ? [
      for idx, policy in definition :
      "${policy}_${var.env}"
    ] :
    env == "all" ? definition :
    env == var.env ? definition : [""]
  ])) : policy_name if policy_name != ""]


  self_keys = distinct([for idx, key in local.self_iam_policies : "iam_policy_${local.snake_full_name}_${key}"])
  cross_tenant_keys = distinct(flatten([
    for external_tenant, policies in local.cross_tenant_policies :
    [for policy in policies : "iam_policy_${replace(external_tenant, "-", "_")}_${replace(policy, "-", "_")}"]
  ]))
  infra_keys = distinct([for idx, key in local.infra_policies : key])
}

output "iam_policies" {
  value = {
    self_keys         = local.self_keys
    cross_tenant_keys = local.cross_tenant_keys
    infra_keys        = local.infra_keys
    all_keys = distinct(concat(
      local.self_keys,
      local.cross_tenant_keys,
      local.infra_keys
    ))
  }
}
