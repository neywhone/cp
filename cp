resource "aws_iam_role_policy_attachment" "self_policy_attachement" {
  for_each   = [for policy in tenant.iam_policies.self : policy if var.tenant.aws_iam_role_name != null]
  policy_arn = each.value
  role       = var.tenant.aws_iam_role_name
}
