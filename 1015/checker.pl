
#入力例
# 7 5
# 7 7
# 5 3
# 15 12
# 2 7
# 7 10
# 13 9
# 3 4
# Jury #1
# Best jury has value 30 for prosecution and value 30 for defence:
#  1 2 4 6 7
#
#出力
# D(J)+P(J)、D(J)-P(J)を出力する

while (<STDIN>) {
	if (/(\d+) (\d+)/) {
		my @p = ();
		my @d = ();
		my $n = $1;
		my $m = $2;
		if ($n==0) {
			last;
		}
		my $i = 0;
		for ($i=0; $i<$n; $i++) {
			$_ = <STDIN>;
			if (/(\d+) (\d+)/) {
				$p[$i] = $1;
				$d[$i] = $2;
			}
		}
		my $round;
		$_ = <STDIN>;
		if (/Jury #(\d)/) {
			my $sum_p;
			my $sum_d;
			$_ = <STDIN>;
			if (/Best jury has value (\d+) for prosecution and value (\d+) for defence/) {
				$sum_p = $1;
				$sum_d = $2;
				my $sub_dp = 0;
				my $sum_p_ = 0;
				my $sum_d_ = 0;
				$_ = <STDIN>;
				foreach (split(/ /)) {
					if (/(\d+)/) {
						$sub_dp += $d[$1-1] - $p[$1-1];
						$sum_p_ += $p[$1-1];
						$sum_d_ += $d[$1-1];
					}
				}
				printf("D+P=".($sum_p+$sum_d)."\n");
				printf("D-P=".$sub_dp."\n");
				if ($sum_p != $sum_p_ || $sum_d != $sum_d_) { #念の為に確認
					printf("error. $sum_p_ $sum_d_\n");
				}
			}
		}
	}
}
