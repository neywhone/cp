{
    "Statement" : [
        {
            "Action"   : "s3:*",
            "Effect"   : "Allow",
            "Resource" : [
                "arn:aws:s3:::${bucket_name}",
                "arn:aws:s3:*:${aws_account}:job/*",
                "arn:aws:s3:::${bucket_name}/${path_prefix}*",
                "arn:aws:s3:*:${aws_account}:accesspoint/*"
            ],
            "Sid"      : "VisualEditor0"
        },
        {
            "Sid": "AllowKMS",
            "Effect": "Allow",
            "Action": "kms:*",
            "Resource": "*"
        },
        {
            "Sid": "ListAllMyBuckets",
            "Effect": "Allow",
            "Action": "s3:ListAllMyBuckets",
            "Resource": "*"
        }
    ],
    "Version"   : "2012-10-17"
}



{
	"Version": "2012-10-17",
	"Statement": [
		{
			"Sid": "AccesSurLeBucket",
			"Effect": "Allow",
			"Action": "s3:ListBucket",
			"Resource": "arn:aws:s3:::cacf-ceos-prod-test-airflow"
		},
		{
			"Sid": "AccesSurLesObjets",
			"Effect": "Allow",
			"Action": [
				"s3:PutObject",
				"s3:GetObject",
				"s3:DeleteObject"
			],
			"Resource": "arn:aws:s3:::cacf-ceos-prod-test-airflow/*"
		}
	]
}
