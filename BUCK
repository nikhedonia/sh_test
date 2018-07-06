
cxx_binary(
  name = "main",
  srcs = ["test/main.cpp"],
)


genrule(
  name = "res",
  out =".",
  srcs = glob(["test/res/*"]),
  cmd = "cp -r $SRCS $OUT"
)


sh_binary(
  name="test-runner",
  main=":main",
  resources=[":res"]
)

sh_test(
  name="test",
  test=":test-runner"
)

