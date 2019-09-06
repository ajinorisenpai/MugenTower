# VisualStudioで動くようにwinsrcフォルダを生成する
rm -rf winsrc
mkdir winsrc

# 全てのソースファイルを第一階層に
find src -name "*.hpp" | xargs -I% cp % winsrc
find src -name "*.cpp" | xargs -I% cp % winsrc
find src -name "*.h"  | xargs -I% cp % winsrc

# Resource関数の削除
find winsrc -name "*.hpp" -print0 | xargs -0 sed  -i.bak 's/Resource(\([^)]*\))/\1/g'
find winsrc -name "*.cpp" -print0 | xargs -0 sed -i.bak 's/Resource(\([^)]*\))/\1/g'
find winsrc -name "*.h" -print0 | xargs -0 sed -i.bak 's/Resource(\([^)]*\))/\1/g'

rm -f winsrc/*.bak

# 文字コード修正
find winsrc -name "*.hpp" -exec nkf --overwrite --oc=UTF-8-BOM {} \;
find winsrc -name "*.cpp" -exec nkf --overwrite --oc=UTF-8-BOM {} \;
find winsrc -name "*.h" -exec nkf --overwrite --oc=UTF-8-BOM {} \;