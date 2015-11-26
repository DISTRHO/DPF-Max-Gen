#include "gen_exported.h"

namespace gen_exported {


/*******************************************************************************************************************
Copyright (c) 2012 Cycling '74

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/


// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State { 
	CommonState __commonstate;
	Delay m_delay_24;
	Delay m_delay_14;
	Delay m_delay_15;
	Delay m_delay_13;
	Delay m_delay_12;
	Delay m_delay_23;
	Delay m_delay_16;
	Delay m_delay_18;
	Delay m_delay_17;
	Delay m_delay_20;
	Delay m_delay_19;
	Delay m_delay_21;
	Delay m_delay_22;
	Delta m_delta_39;
	Delta m_delta_48;
	Delta m_delta_42;
	Delta m_delta_45;
	Phasor m_phasor_38;
	Sah m_sah_47;
	Sah m_sah_46;
	Sah m_sah_44;
	Sah m_sah_41;
	Sah m_sah_43;
	Sah m_sah_40;
	Sah m_sah_49;
	Sah m_sah_50;
	double m_history_10;
	double m_history_7;
	double m_history_6;
	double m_history_8;
	double m_history_9;
	double samples_to_seconds;
	double m_history_5;
	double m_history_3;
	double samplerate;
	double m_history_4;
	double m_history_1;
	double m_y_2;
	double m_y_11;
	double m_window_37;
	double m_early_35;
	double m_damping_27;
	double m_spread_28;
	double m_ratio_26;
	double m_shift_25;
	double m_mix_36;
	double m_blur_29;
	double m_decay_31;
	double m_roomsize_30;
	double m_cutoff_33;
	double m_tail_34;
	double m_tone_32;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = 0;
		m_y_2 = 0;
		m_history_3 = 0;
		m_history_4 = 0;
		m_history_5 = 0;
		m_history_6 = 0;
		m_history_7 = 0;
		m_history_8 = 0;
		m_history_9 = 0;
		m_history_10 = 0;
		m_y_11 = 0;
		m_delay_12.reset("m_delay_12", 5000);
		m_delay_13.reset("m_delay_13", 7000);
		m_delay_14.reset("m_delay_14", 15000);
		m_delay_15.reset("m_delay_15", 16000);
		m_delay_16.reset("m_delay_16", 6000);
		m_delay_17.reset("m_delay_17", 88200);
		m_delay_18.reset("m_delay_18", 48000);
		m_delay_19.reset("m_delay_19", 10000);
		m_delay_20.reset("m_delay_20", 12000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_delay_24.reset("m_delay_24", 48000);
		m_shift_25 = 0.5;
		m_ratio_26 = 2;
		m_damping_27 = 0.75;
		m_spread_28 = 25;
		m_blur_29 = 0.25;
		m_roomsize_30 = 75;
		m_decay_31 = 11;
		m_tone_32 = 0.5;
		m_cutoff_33 = 3000;
		m_tail_34 = 0.25;
		m_early_35 = 0.25;
		m_mix_36 = 0.75;
		m_window_37 = 100;
		samples_to_seconds = (1 / samplerate);
		m_phasor_38.reset(0);
		m_delta_39.reset(0);
		m_sah_40.reset(0);
		m_sah_41.reset(0);
		m_delta_42.reset(0);
		m_sah_43.reset(0);
		m_sah_44.reset(0);
		m_delta_45.reset(0);
		m_sah_46.reset(0);
		m_sah_47.reset(0);
		m_delta_48.reset(0);
		m_sah_49.reset(0);
		m_sah_50.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) { 
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) { 
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) { 
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		double rsub_1933 = (1 - m_tone_32);
		double expr_2527 = safepow(0.001, safediv(1, (m_decay_31 * 44100)));
		double expr_2518 = safediv(((m_cutoff_33 * 2) * 3.1415926535898), 44100);
		double cos_1776 = cos(expr_2518);
		double mul_1774 = (cos_1776 * -2);
		double add_1772 = (mul_1774 + 1);
		double expr_2528 = safediv((m_roomsize_30 * 44100), 340);
		double mul_1922 = (expr_2528 * 0.63245);
		double expr_2519 = (-safepow(expr_2527, mul_1922));
		double mul_1923 = (expr_2528 * 0.7071);
		double expr_2520 = (-safepow(expr_2527, mul_1923));
		double mul_1925 = (expr_2528 * 1);
		double expr_2526 = (-safepow(expr_2527, mul_1925));
		double mul_1924 = (expr_2528 * 0.81649);
		double expr_2521 = (-safepow(expr_2527, mul_1924));
		double mul_1919 = (expr_2528 * 0.000527);
		int int_1918 = int(mul_1919);
		double mstosamps_1760 = (m_window_37 * (samplerate * 0.001));
		double mul_1859 = (m_spread_28 * -0.380445);
		double add_1858 = (mul_1859 + 931);
		double rsub_1855 = (1341 - add_1858);
		double mul_1868 = (int_1918 * rsub_1855);
		double add_1848 = (expr_2528 + 5);
		double expr_2522 = safepow(expr_2527, add_1848);
		double mul_1887 = (m_spread_28 * 0.376623);
		double add_1886 = (mul_1887 + 931);
		double rsub_1883 = (1341 - add_1886);
		double mul_1894 = (int_1918 * rsub_1883);
		double mul_1854 = (expr_2528 * 0.41);
		double add_1851 = (mul_1854 + 5);
		double expr_2525 = safepow(expr_2527, add_1851);
		double mul_1853 = (expr_2528 * 0.3);
		double add_1850 = (mul_1853 + 5);
		double expr_2524 = safepow(expr_2527, add_1850);
		double mul_1852 = (expr_2528 * 0.155);
		double add_1849 = (mul_1852 + 5);
		double expr_2523 = safepow(expr_2527, add_1849);
		double rsub_1747 = (1 - m_ratio_26);
		double mul_1746 = (rsub_1747 * 1000);
		double div_1745 = safediv(mul_1746, m_window_37);
		samples_to_seconds = (1 / samplerate);
		double mul_1917 = (expr_2528 * 0.110732);
		double mul_1861 = (m_spread_28 * -0.568366);
		double add_1857 = (mul_1861 + 369);
		double rsub_1856 = (add_1858 - add_1857);
		double mul_1875 = (int_1918 * rsub_1856);
		double mul_1903 = (m_spread_28 * 0.125541);
		double add_1885 = (mul_1903 + 369);
		double rsub_1884 = (add_1886 - add_1885);
		double mul_1901 = (int_1918 * rsub_1884);
		double add_1860 = (mul_1861 + 159);
		double mul_1882 = (int_1918 * add_1860);
		double add_1902 = (mul_1903 + 159);
		double mul_1910 = (int_1918 * add_1902);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_1697 = noise();
			double abs_1715 = fabs(noise_1697);
			double mul_1721 = (abs_1715 * m_blur_29);
			double noise_1698 = noise();
			double abs_1716 = fabs(noise_1698);
			double mul_1724 = (abs_1716 * m_blur_29);
			double noise_1699 = noise();
			double abs_1717 = fabs(noise_1699);
			double mul_1727 = (abs_1717 * m_blur_29);
			double noise_1696 = noise();
			double abs_1714 = fabs(noise_1696);
			double mul_1718 = (abs_1714 * m_blur_29);
			double mul_1770 = (mul_1774 * m_y_2);
			double tap_1822 = m_delay_24.read_linear(mul_1922);
			double mul_1818 = (tap_1822 * expr_2519);
			double mix_2571 = (mul_1818 + (m_damping_27 * (m_history_10 - mul_1818)));
			double mix_1820 = mix_2571;
			double tap_1828 = m_delay_23.read_linear(mul_1923);
			double mul_1824 = (tap_1828 * expr_2520);
			double mix_2572 = (mul_1824 + (m_damping_27 * (m_history_9 - mul_1824)));
			double mix_1826 = mix_2572;
			double tap_1930 = m_delay_22.read_linear(mul_1925);
			double mul_1921 = (tap_1930 * expr_2526);
			double mix_2573 = (mul_1921 + (m_damping_27 * (m_history_8 - mul_1921)));
			double mix_1928 = mix_2573;
			double tap_1834 = m_delay_21.read_linear(mul_1924);
			double mul_1830 = (tap_1834 * expr_2521);
			double mix_2574 = (mul_1830 + (m_damping_27 * (m_history_7 - mul_1830)));
			double mix_1832 = mix_2574;
			double tap_1867 = m_delay_20.read_linear(mul_1868);
			double mul_1865 = (tap_1867 * 0.625);
			double add_1812 = (mix_1928 + mix_1832);
			double add_1810 = (mix_1826 + mix_1820);
			double add_1805 = (add_1812 + add_1810);
			double mul_1788 = (add_1805 * 0.5);
			double sub_1809 = (add_1812 - add_1810);
			double mul_1791 = (sub_1809 * 0.5);
			double tap_1893 = m_delay_19.read_linear(mul_1894);
			double mul_1891 = (tap_1893 * 0.625);
			double sub_1811 = (mix_1928 - mix_1832);
			double sub_1808 = (mix_1826 - mix_1820);
			double sub_1807 = (sub_1811 - sub_1808);
			double mul_1790 = (sub_1807 * 0.5);
			double add_1806 = (sub_1811 + sub_1808);
			double rsub_1804 = (0 - add_1806);
			double mul_1789 = (rsub_1804 * 0.5);
			double tap_1836 = m_delay_18.read_linear(add_1851);
			double tap_1837 = m_delay_18.read_linear(add_1850);
			double tap_1838 = m_delay_18.read_linear(add_1849);
			double tap_1839 = m_delay_18.read_linear(add_1848);
			double mul_1840 = (tap_1839 * expr_2522);
			double add_1813 = (mul_1788 + mul_1840);
			double mul_1846 = (tap_1836 * expr_2525);
			double add_1816 = (mul_1791 + mul_1846);
			double mul_1844 = (tap_1837 * expr_2524);
			double add_1815 = (mul_1790 + mul_1844);
			double mul_1842 = (tap_1838 * expr_2523);
			double add_1814 = (mul_1789 + mul_1842);
			double phasor_1766 = m_phasor_38(div_1745, samples_to_seconds);
			double add_1744 = ((m_history_6 + phasor_1766) + 0.5);
			double mod_1743 = safemod(add_1744, 1);
			double delta_1723 = m_delta_39(mod_1743);
			double sah_1702 = m_sah_40(mul_1721, delta_1723, 0);
			double sah_1722 = m_sah_41(mstosamps_1760, delta_1723, 0);
			double mul_1711 = (sah_1722 * mod_1743);
			double sub_1742 = (mod_1743 - 0.5);
			double mul_1741 = (sub_1742 * 3.1415926535898);
			double cos_1740 = cos(mul_1741);
			double mul_1730 = (cos_1740 * cos_1740);
			double add_1759 = ((m_history_5 + phasor_1766) + 0.25);
			double mod_1758 = safemod(add_1759, 1);
			double delta_1726 = m_delta_42(mod_1758);
			double sah_1704 = m_sah_43(mul_1724, delta_1726, 0);
			double sah_1725 = m_sah_44(mstosamps_1760, delta_1726, 0);
			double mul_1712 = (sah_1725 * mod_1758);
			double sub_1757 = (mod_1758 - 0.5);
			double mul_1756 = (sub_1757 * 3.1415926535898);
			double cos_1755 = cos(mul_1756);
			double mul_1731 = (cos_1755 * cos_1755);
			double add_1765 = ((m_history_4 + phasor_1766) + 0);
			double mod_1764 = safemod(add_1765, 1);
			double delta_1707 = m_delta_45(mod_1764);
			double sah_1706 = m_sah_46(mul_1727, delta_1707, 0);
			double sah_1728 = m_sah_47(mstosamps_1760, delta_1707, 0);
			double mul_1713 = (sah_1728 * mod_1764);
			double sub_1763 = (mod_1764 - 0.5);
			double mul_1762 = (sub_1763 * 3.1415926535898);
			double cos_1761 = cos(mul_1762);
			double mul_1732 = (cos_1761 * cos_1761);
			double add_1738 = ((m_history_3 + phasor_1766) + 0.75);
			double mod_1737 = safemod(add_1738, 1);
			double delta_1720 = m_delta_48(mod_1737);
			double sah_1700 = m_sah_49(mul_1718, delta_1720, 0);
			double sah_1719 = m_sah_50(mstosamps_1760, delta_1720, 0);
			double mul_1710 = (sah_1719 * mod_1737);
			double tap_1751 = m_delay_17.read_linear(mul_1713);
			double tap_1752 = m_delay_17.read_linear(mul_1712);
			double tap_1753 = m_delay_17.read_linear(mul_1711);
			double tap_1754 = m_delay_17.read_linear(mul_1710);
			double mul_1739 = (tap_1753 * mul_1730);
			double mul_1748 = (tap_1752 * mul_1731);
			double mul_1749 = (tap_1751 * mul_1732);
			double sub_1736 = (mod_1737 - 0.5);
			double mul_1735 = (sub_1736 * 3.1415926535898);
			double cos_1734 = cos(mul_1735);
			double mul_1729 = (cos_1734 * cos_1734);
			double mul_1733 = (tap_1754 * mul_1729);
			double mul_1771 = ((((mul_1749 + mul_1748) + mul_1739) + mul_1733) * add_1772);
			double sub_1768 = (mul_1771 - (m_y_11 + mul_1770));
			double mix_2575 = (in1 + (m_shift_25 * (sub_1768 - in1)));
			double mix_1709 = mix_2575;
			double mul_1782 = (mix_1709 * 0.707);
			double mix_2576 = (mul_1782 + (rsub_1933 * (m_history_1 - mul_1782)));
			double mix_1932 = mix_2576;
			double tap_1916 = m_delay_16.read_linear(mul_1917);
			double tap_1874 = m_delay_15.read_linear(mul_1875);
			double mul_1872 = (tap_1874 * 0.625);
			double mul_1914 = (tap_1916 * 0.75);
			double sub_1913 = (mix_1932 - mul_1914);
			double mul_1912 = (sub_1913 * 0.75);
			double add_1911 = (mul_1912 + tap_1916);
			double tap_1900 = m_delay_14.read_linear(mul_1901);
			double mul_1898 = (tap_1900 * 0.625);
			double tap_1881 = m_delay_13.read_linear(mul_1882);
			double mul_1879 = (tap_1881 * 0.75);
			double tap_1909 = m_delay_12.read_linear(mul_1910);
			double mul_1907 = (tap_1909 * 0.75);
			double mul_1803 = (mul_1791 * m_tail_34);
			double mul_1801 = (mul_1789 * m_tail_34);
			double add_1787 = (mul_1803 + mul_1801);
			double mul_1802 = (mul_1790 * m_tail_34);
			double mul_1800 = (mul_1788 * m_tail_34);
			double add_1786 = (mul_1802 + mul_1800);
			double sub_1795 = (add_1787 - add_1786);
			double mul_1799 = (mul_1846 * m_early_35);
			double mul_1797 = (mul_1842 * m_early_35);
			double add_1785 = (mul_1799 + mul_1797);
			double mul_1798 = (mul_1844 * m_early_35);
			double mul_1796 = (mul_1840 * m_early_35);
			double add_1784 = (mul_1798 + mul_1796);
			double sub_1794 = (add_1785 - add_1784);
			double add_1781 = (sub_1795 + sub_1794);
			double add_1783 = (add_1781 + mix_1709);
			double sub_1878 = (add_1783 - mul_1879);
			double mul_1877 = (sub_1878 * 0.75);
			double add_1876 = (mul_1877 + tap_1881);
			double sub_1871 = (add_1876 - mul_1872);
			double mul_1870 = (sub_1871 * 0.625);
			double add_1869 = (mul_1870 + tap_1874);
			double sub_1864 = (add_1869 - mul_1865);
			double mul_1863 = (sub_1864 * 0.625);
			double add_1862 = (mul_1863 + tap_1867);
			double mul_1780 = (add_1862 * m_mix_36);
			double out2 = (mul_1780 + in1);
			double add_1793 = (add_1781 + mix_1709);
			double sub_1906 = (add_1793 - mul_1907);
			double mul_1905 = (sub_1906 * 0.75);
			double add_1904 = (mul_1905 + tap_1909);
			double sub_1897 = (add_1904 - mul_1898);
			double mul_1896 = (sub_1897 * 0.625);
			double add_1895 = (mul_1896 + tap_1900);
			double sub_1890 = (add_1895 - mul_1891);
			double mul_1889 = (sub_1890 * 0.625);
			double add_1888 = (mul_1889 + tap_1893);
			double mul_1792 = (add_1888 * m_mix_36);
			double out1 = (mul_1792 + in1);
			double y2_next_2542 = m_y_2;
			double history_1819_next_2543 = mix_1820;
			double history_1825_next_2544 = mix_1826;
			double history_1927_next_2545 = mix_1928;
			double history_1831_next_2546 = mix_1832;
			double history_1703_next_2547 = sah_1702;
			double history_1705_next_2548 = sah_1704;
			double history_1708_next_2549 = sah_1706;
			double history_1701_next_2550 = sah_1700;
			double y1_next_2551 = sub_1768;
			double history_1931_next_2552 = mix_1932;
			m_delay_24.write(add_1813);
			m_delay_23.write(add_1814);
			m_delay_22.write(add_1816);
			m_delay_21.write(add_1815);
			m_delay_20.write(sub_1864);
			m_delay_19.write(sub_1890);
			m_delay_18.write(add_1911);
			m_delay_17.write(in1);
			m_delay_16.write(sub_1913);
			m_delay_15.write(sub_1871);
			m_delay_14.write(sub_1897);
			m_delay_13.write(sub_1878);
			m_delay_12.write(sub_1906);
			m_y_11 = y2_next_2542;
			m_history_10 = history_1819_next_2543;
			m_history_9 = history_1825_next_2544;
			m_history_8 = history_1927_next_2545;
			m_history_7 = history_1831_next_2546;
			m_history_6 = history_1703_next_2547;
			m_history_5 = history_1705_next_2548;
			m_history_4 = history_1708_next_2549;
			m_history_3 = history_1701_next_2550;
			m_y_2 = y1_next_2551;
			m_history_1 = history_1931_next_2552;
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			m_delay_17.step();
			m_delay_18.step();
			m_delay_19.step();
			m_delay_20.step();
			m_delay_21.step();
			m_delay_22.step();
			m_delay_23.step();
			m_delay_24.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_shift(double _value) {
		m_shift_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_26 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(double _value) {
		m_spread_28 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_29 = (_value < 0.01 ? 0.01 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_30 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_31 = (_value < 0.1 ? 0.1 : (_value > 360 ? 360 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_33 = (_value < 0 ? 0 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_tail(double _value) {
		m_tail_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_early(double _value) {
		m_early_35 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_36 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_window(double _value) {
		m_window_37 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	
} State;


/// 
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs 

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 13; }

/// Assistive lables for the signal inputs and outputs 

const char * gen_kernel_innames[] = { "in1" };
const char * gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) { 
	State * self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) { 
	State * self = (State *)cself;
	self->reset(cself->sr, cself->vs); 
}

/// Set a parameter of a State object 

void setparameter(CommonState *cself, long index, double value, void *ref) {
	State * self = (State *)cself;
	switch (index) {
		case 0: self->set_shift(value); break;
		case 1: self->set_ratio(value); break;
		case 2: self->set_damping(value); break;
		case 3: self->set_spread(value); break;
		case 4: self->set_blur(value); break;
		case 5: self->set_roomsize(value); break;
		case 6: self->set_decay(value); break;
		case 7: self->set_tone(value); break;
		case 8: self->set_cutoff(value); break;
		case 9: self->set_tail(value); break;
		case 10: self->set_early(value); break;
		case 11: self->set_mix(value); break;
		case 12: self->set_window(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_shift_25; break;
		case 1: *value = self->m_ratio_26; break;
		case 2: *value = self->m_damping_27; break;
		case 3: *value = self->m_spread_28; break;
		case 4: *value = self->m_blur_29; break;
		case 5: *value = self->m_roomsize_30; break;
		case 6: *value = self->m_decay_31; break;
		case 7: *value = self->m_tone_32; break;
		case 8: *value = self->m_cutoff_33; break;
		case 9: *value = self->m_tail_34; break;
		case 10: *value = self->m_early_35; break;
		case 11: *value = self->m_mix_36; break;
		case 12: *value = self->m_window_37; break;
		
		default: break;
	}
}

/// Allocate and configure a new State object and it's internal CommonState:

void * create(double sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(13 * sizeof(ParamInfo));
	self->__commonstate.numparams = 13;
	// initialize parameter 0 ("m_shift_25")
	pi = self->__commonstate.params + 0;
	pi->name = "shift";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shift_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ratio_26")
	pi = self->__commonstate.params + 1;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_damping_27")
	pi = self->__commonstate.params + 2;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_spread_28")
	pi = self->__commonstate.params + 3;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_blur_29")
	pi = self->__commonstate.params + 4;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_roomsize_30")
	pi = self->__commonstate.params + 5;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_decay_31")
	pi = self->__commonstate.params + 6;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 360;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_tone_32")
	pi = self->__commonstate.params + 7;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_cutoff_33")
	pi = self->__commonstate.params + 8;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_tail_34")
	pi = self->__commonstate.params + 9;
	pi->name = "tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tail_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_early_35")
	pi = self->__commonstate.params + 10;
	pi->name = "early";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_early_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_mix_36")
	pi = self->__commonstate.params + 11;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_window_37")
	pi = self->__commonstate.params + 12;
	pi->name = "window";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) { 
	State * self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self; 
}


} // gen_exported::
