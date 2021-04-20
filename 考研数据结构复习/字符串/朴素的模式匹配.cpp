int strMatching(string str1, string str2) {
		int i=0, j = 0;
		int len1 = str1.length(), len2 = str2.length();
		if (len2 == 0) return 0;
		if (len1 < len2) return -1;
		while (i < len1 && j < len2) {
			if (str1[i] == str2[j]) {
				i++;
				j++;
			}
			else {
				i = i - j + 1;
				j = 0;
			}
		}
		if (j >= len2)
			return i - len2;
		else
			return -1;
}