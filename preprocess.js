#!/usr/bin/env node
// Run this after cloning this repo with nodejs (16+)

const fs = require("node:fs");

const tmpToken = "\\__@-@__/";

const license = fs
    .readFileSync("./LICENSE")
    .toString()
    .split("\n")
    .slice(2)
    .join("\n")
    .trim()
    .replaceAll("\n\n", tmpToken)
    .replaceAll("\n", " ")
    .replaceAll(tmpToken, "\n\n");

fs.writeFileSync("./WinUI/LICENSE.g.txt", license);
