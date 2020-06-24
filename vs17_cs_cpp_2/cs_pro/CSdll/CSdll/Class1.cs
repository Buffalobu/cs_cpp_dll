using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CII.GCMS.NISTSCH.NistSearch;

namespace CSdll
{
    public class Class1
    {
        public int csAdd(int a, int b)
        {
            return a + b;
        }

        public bool nist_sch(uint[] mass, uint[] abund, ref int resCnt, ref uint[] peakNums/*, ref String[] formula */)
        {
            NistPathHelper.IsUseMainLib = true;
            NistPathHelper.FULL_PATH_TO_MAIN_LIBRARY = @"G:\NIST11\MSSEARCH\mainlib";
            NistPathHelper.FULL_PATH_TO_WORK_DIR = @"G:\Nist11";
            NistPathHelper.FULL_PATH_TO_USER_LIBRARY = @"G:\Nist11\MSSEARCH\userlib1";
            NistPathHelper.FULL_PATH_TO_REPLICATE_LIBRARY = @"G:\Nist11\MSSEARCH\replib";
            NistPathHelper.FULL_PATH_TO_USER_LIBRARY2 = @"G:\Nist11\MSSEARCH\userlib2";

        //    uint[] mass = new uint[] { 91, 92, 78, 77 };
        //    uint[] abund = new uint[] { 100, 67, 34, 30 };

            string path = NistPathHelper.FULL_PATH_TO_MAIN_LIBRARY;
            if (!System.IO.Directory.Exists(path)) {
                return false;
            }
            List<NistMSData> nistSearchedDatas = NistLibSeach.Search(mass, abund, 1);
            int count = nistSearchedDatas.Count;
            if (count <= 0)
                return false;
            peakNums = new uint[count];
         //   formula = new String[count];
            for (int i = 0; i < nistSearchedDatas.Count; i++) {
                peakNums[i] = nistSearchedDatas[i].PeakNum;
         //       formula[i] = nistSearchedDatas[i].Formula;
            }
            resCnt = count;
            return true;
        }

        public bool nist_sch_one(uint[] mass, uint[] abund, ref int resCnt, ref int CAS, ref uint MW, 
            ref int Match, ref String name, ref uint PeakNum, ref int Prob, ref int R_Match, ref String formula)
        {
            NistPathHelper.IsUseMainLib = true;
            NistPathHelper.FULL_PATH_TO_MAIN_LIBRARY = @"G:\NIST11\MSSEARCH\mainlib";
            NistPathHelper.FULL_PATH_TO_WORK_DIR = @"G:\Nist11";
            NistPathHelper.FULL_PATH_TO_USER_LIBRARY = @"G:\Nist11\MSSEARCH\userlib1";
            NistPathHelper.FULL_PATH_TO_REPLICATE_LIBRARY = @"G:\Nist11\MSSEARCH\replib";
            NistPathHelper.FULL_PATH_TO_USER_LIBRARY2 = @"G:\Nist11\MSSEARCH\userlib2";

            string path = NistPathHelper.FULL_PATH_TO_MAIN_LIBRARY;
            if (!System.IO.Directory.Exists(path))
            {
                return false;
            }
            List<NistMSData> sch_data = NistLibSeach.Search(mass, abund, 1);
            int count = sch_data.Count;
            if (count <= 0)
                return false;
            resCnt = count;
            CAS     = sch_data[0].CAS;
            MW      = sch_data[0].MW;
            Match   = sch_data[0].Match;
            name    = sch_data[0].Name;
        //    name = (byte[])((Array)Encoding.Default.GetBytes(s_name));
            PeakNum = sch_data[0].PeakNum;
            Prob    = sch_data[0].Prob;
            R_Match = sch_data[0].R_Match;
            formula = sch_data[0].Formula;
       //     formula = (byte[])((Array)Encoding.Default.GetBytes(s_formula));
            return true;
        }
    }
}
