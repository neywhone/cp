resource "aws_iam_policy" "iam_policy_ceos_s3_ia_knowledge_space_rw" {
  name = "iam-policy-ceos-s3-ai-knowledge-${var.tenant.env}-${local.team}-${var.tenant.name}-rw"
  policy = templatefile("${path.module}/../../policies/s3-iam-policy-ai-knowledge-allow-rw.tftpl",
    {
      bucket_name = "cacf-ceos-test-airflow"
      aws_account = var.aws_account_id
      path_prefix = local.path_prefix
    }
  )
}
