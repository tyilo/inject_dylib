task :default => [:build]

SOURCES = "main.c task_vaccine/build/x86_64/task_vaccine.a"
COMPILER = "clang"

task :build do
	Dir.chdir("task_vaccine") do
		ruby "-S", "rake", "static_64"
	end
	system("#{COMPILER} #{SOURCES} -o inject_dylib")
end
