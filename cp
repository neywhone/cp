resource "aws_iam_role_policy_attachment" "knowledge_space_rw_attachment" {
  count = (local.team == "iagen" && var.tenant.name == "airflow" && var.tenant.aws_iam_role_name != null) ? 1 : 0

  policy_arn = module.tenant_policies["iagen-develop-airflow"].aws_iam_policy.iam_policy_ceos_s3_ia_knowledge_space_rw[0].arn
  role       = var.tenant.aws_iam_role_name
}
