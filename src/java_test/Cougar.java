import java.util.ArrayList;
import java.util.List;

public class TestB {
	public static void main(String[] args) {
		List<String> list = new ArrayList<>();
		list.add("a");
		list.add("b");
		list.add("c");

		for (String str : list) {
			if (str.equals("b")) {
				list.remove(str);
			} else {
				System.out.println(str);
			}
		}

		int[][] array1 = new int[][] {};
		int[] array2;
		array2 = new int[2];
		int array3[];
		array3 = new int[] { 1, 2, 3 };
		System.arraycopy(array3, 0, array2, 0, array3.length-1);

		for (int a : array2) {
			System.out.println(a);
		}

		String st = "TRUE";
		Boolean bl = Boolean.valueOf(st);
		System.out.println(bl);

		TestB testB = new TestB();
		int c = 10;
		System.out.println(160 / 100);

		System.out.println(st.contains("F"));

		castA D = new castA();
		castB  cB = (castB)D;

	}
}

class castA {
}

class castB  {
}
