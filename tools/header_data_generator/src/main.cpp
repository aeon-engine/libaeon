// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include "application.h"

int main(int argc, char *argv[])
{
    aeon::header_data_generator::application app;
    return app.main(argc, argv);
}
