{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "AccesSurLeBucket",
      "Effect": "Allow",
      "Action": "s3:ListBucket",
      "Resource": "arn:aws:s3:::${bucket_name}"
    },
    {
      "Sid": "AccesSurLesObjets",
      "Effect": "Allow",
      "Action": [
        "s3:PutObject",
        "s3:GetObject",
        "s3:DeleteObject"
      ],
      "Resource": "arn:aws:s3:::${bucket_name}/*"
    }
  ]
}
