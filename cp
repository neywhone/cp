resource "aws_iam_role_policy_attachment" "self_policy_attachement" {
  for_each   = [for policy in tenant.iam_policies.self : policy if var.tenant.aws_iam_role_name != null]
  policy_arn = each.value
  role       = var.tenant.aws_iam_role_name
}


output "policies" {
  value = {
    s3_datalake_space_rw = aws_iam_policy.iam_policy_ceos_s3_datalake_space_rw.arn
    s3_datalake_space_ro = aws_iam_policy.iam_policy_ceos_s3_datalake_space_ro.arn
    s3_datalake_space_wo = aws_iam_policy.iam_policy_ceos_s3_datalake_space_wo.arn
  }
}


locals {
  raw_team    = lookup(var.tenant.team, "key", "core")
  team        = local.raw_team == null ? "core" : replace(local.raw_team, "_", "-")
  path_prefix = var.path_prefix != null ? var.path_prefix : "datalake/${var.tenant.env}-${local.team}/${var.tenant.name}/"

}

resource "aws_iam_policy" "iam_policy_ceos_s3_datalake_space_rw" {
  name = "iam-policy-ceos-s3-${var.policy_prefix}-${var.tenant.env}-${local.team}-${var.tenant.name}-rw"
  policy = templatefile("${path.module}/../../policies/s3-iam-policy-allow-rw.tftpl",
    {
      bucket_name = var.dwh_bucket_name
      aws_account = var.aws_account_id
      path_prefix = local.path_prefix
    }
  )
}

resource "aws_iam_policy" "iam_policy_ceos_s3_ia_knowledge_space_rw" {
  count = (local.team == "iagen" && var.tenant.name == "airflow") ? 1 : 0

  name = "iam-policy-ceos-s3-ai-knowledge-${var.tenant.env}-${local.team}-${var.tenant.name}-rw"
  policy = templatefile("${path.module}/../../policies/s3-iam-policy-ai-knowledge-allow-rw.tftpl",
    {
      bucket_name = "cacf-ceos-test-airflow"
      aws_account = var.aws_account_id
      path_prefix = local.path_prefix
    }
  )
}

resource "aws_iam_policy" "iam_policy_ceos_s3_datalake_space_ro" {
  name = "iam-policy-ceos-s3-${var.policy_prefix}-${var.tenant.env}-${local.team}-${var.tenant.name}-ro"
  policy = templatefile("${path.module}/../../policies/s3-iam-policy-allow-ro.tftpl",
    {
      bucket_name = var.dwh_bucket_name
      aws_account = var.aws_account_id
      path_prefix = local.path_prefix
    }
  )
}

resource "aws_iam_policy" "iam_policy_ceos_s3_datalake_space_wo" {
  name = "iam-policy-ceos-s3-${var.policy_prefix}-${var.tenant.env}-${local.team}-${var.tenant.name}-wo"
  policy = templatefile("${path.module}/../../policies/s3-iam-policy-allow-put-only.tftpl",
    {
      bucket_name = var.dwh_bucket_name
      aws_account = var.aws_account_id
      path_prefix = local.path_prefix

    }
  )
}

variable "dwh_bucket_name" {
  type = string
}

variable "aws_account_id" {
  type = string
}

variable "tenant" {
  type = object({
    env  = string
    name = string
    team = any
  })
}

variable "policy_prefix" {
  type    = string
  default = "datalake"
}
variable "path_prefix" {
  type        = string
  description = "Surcharge le prefix S3 par défaut"
  default     = null
}


variable "tenant" {
  type = any
}

variable "policy_mapping" {
  type = map(string)
}

variable "tenants_policy_mapping" {
  type = map(list(string))
}

