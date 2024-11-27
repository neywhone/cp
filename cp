default_self_iam_policies = ["s3_datalake_space_rw"]
  lookup_self_iam_policies  = lookup(local.policies, "self_iam_policies", local.default_self_iam_policies)
  self_iam_policies         = local.lookup_self_iam_policies == null ? local.default_self_iam_policies : local.lookup_self_iam_policies
