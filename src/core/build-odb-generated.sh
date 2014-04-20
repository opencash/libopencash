#!/bin/bash

odb --std c++11 -d sqlite --generate-query --generate-schema -I ../../include -I ../../build/nar-dependencies/compileOpencashOsx-x86_64Debug/include --include-with-brackets --include-prefix "opencash/core" --include-regex '|opencash/core/(.+)-odb\.(.?)xx|$1-odb.$2xx|' -o generated ../../include/opencash/core/Account.h ../../include/opencash/core/Split.h ../../include/opencash/core/Transaction.h ../../include/opencash/core/ManagedObject.h
