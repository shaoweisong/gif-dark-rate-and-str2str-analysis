void extract_layers() {
    // 打开 ROOT 文件
    // TFile* f = TFile::Open("csc_00000001_EmuRUI01_Test_11_000_250507_135921_UTC.root");
    TFile* f = TFile::Open("csc_00000001_EmuRUI01_Test_11_000_250507_111120_UTC.root");
    if (!f || f->IsZombie()) {
        std::cerr << "Cannot open ROOT file!" << std::endl;
        return;
    }

    // 进入目录
    TDirectoryFile* dir = (TDirectoryFile*)f->Get("Test_11_AFEBNoise");
    if (!dir) {
        std::cerr << "Cannot find directory Test_11_AFEBNoise!" << std::endl;
        return;
    }
    // TDirectoryFile* dir2 = (TDirectoryFile*)dir->Get("ME+1.1.GIF");
    TDirectoryFile* dir2 = (TDirectoryFile*)dir->Get("ME+2.1._17_");
    if (!dir2) {
        // std::cerr << "Cannot find directory ME+1.1.GIF!" << std::endl;
        std::cerr << "Cannot find directory ME+2.1._17_!" << std::endl;
        return;
    }

    // 获取 Canvas
    // TCanvas* c = (TCanvas*)dir2->Get("ME+1.1.GIF_11_AFEBNoise_R01");
    TCanvas* c = (TCanvas*)dir2->Get("ME+2.1._17__11_AFEBNoise_R01");
    if (!c) {
        // std::cerr << "Cannot find canvas ME+1.1.GIF_11_AFEBNoise_R01!" << std::endl;
        std::cerr << "Cannot find canvas ME+2.1._17__11_AFEBNoise_R01!" << std::endl;
        return;
    }
    // 获取 Canvas 中的所有原始对象（如直方图）
    TList* primitives = c->GetListOfPrimitives();
    if (!primitives) {
        std::cerr << "No primitives found in the Canvas!" << std::endl;
        return;
    }
    TPad* pad_layer1 = (TPad*)c->FindObject("Pad_Layer_1");
    TPad* pad_layer2 = (TPad*)c->FindObject("Pad_Layer_2");
    TPad* pad_layer3 = (TPad*)c->FindObject("Pad_Layer_3");
    TPad* pad_layer4 = (TPad*)c->FindObject("Pad_Layer_4");
    TPad* pad_layer5 = (TPad*)c->FindObject("Pad_Layer_5");
    TPad* pad_layer6 = (TPad*)c->FindObject("Pad_Layer_6");
    TGraph* gr1 = (TGraph*)pad_layer1->GetListOfPrimitives()->At(6); 
    TGraph* gr2 = (TGraph*)pad_layer2->GetListOfPrimitives()->At(6);
    TGraph* gr3 = (TGraph*)pad_layer3->GetListOfPrimitives()->At(6);
    TGraph* gr4 = (TGraph*)pad_layer4->GetListOfPrimitives()->At(6);
    TGraph* gr5 = (TGraph*)pad_layer5->GetListOfPrimitives()->At(6);
    TGraph* gr6 = (TGraph*)pad_layer6->GetListOfPrimitives()->At(6);
    std::ofstream outfile("graph_points_ME21_old.txt");

    // 图指针数组
    TGraph* graphs[6] = {gr1, gr2, gr3, gr4, gr5, gr6};

    for (int i = 0; i < 6; i++) {
        TGraph* gr = graphs[i];
        if (!gr) continue;

        int n = gr->GetN();
        double x, y;

        outfile << "Graph " << (i+1) << ":\n";

        for (int j = 0; j < n; j++) {
            gr->GetPoint(j, x, y);
            // outfile << x << "\t" << y << "\n";
            outfile << y <<",";
        }

        outfile << "\n";  // 每个图之间空一行
    }

    outfile.close();
    std::cout << "Saved all graph data to graph_points_ME21_old.txt\n";
}