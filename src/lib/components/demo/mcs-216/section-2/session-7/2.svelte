<script lang="ts">
    type Result = {
        status: "PASS" | "FAIL" | "ERROR";
        msg: string;
    };
    let results: Result[] = $state([]);

    const students = [
        { name: "Alice", runLab: () => 2 + 2, expected: 4 },
        {
            name: "Bob",
            runLab: () => {
                throw new ReferenceError("x is not defined");
            },
            expected: 5,
        },
        { name: "Charlie", runLab: () => 10 / 2, expected: 6 },
        { name: "Diana", runLab: () => 5 * 2, expected: 10 },
    ];

    function gradeLabs() {
        results = [];
        for (const s of students) {
            try {
                const actual = s.runLab();
                results.push({
                    status: actual === s.expected ? "PASS" : "FAIL",
                    msg: `${s.name}: ${actual === s.expected ? "✅" : "❌"} (Got ${actual})`,
                });
            } catch (err) {
                const error =
                    err instanceof Error ? err : new Error(String(err));
                results.push({
                    status: "ERROR",
                    msg: `${s.name}: ⚠️ ${error.name}`,
                });
            }
        }
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black rounded-xl mt-5 flex flex-col items-center justify-center gap-4"
>
    <h2 class="text-xl font-semibold text-gray-800">Auto-Grader</h2>
    <button
        onclick={gradeLabs}
        class="px-6 py-2 bg-green-600 text-white rounded-lg hover:bg-green-700 transition"
    >
        Run gradeLabs()
    </button>

    <div class="w-full max-w-md bg-white rounded-xl shadow-md overflow-hidden">
        {#if results.length > 0}
            <div class="divide-y divide-gray-200">
                {#each results as res}
                    <div
                        class="p-4 {res.status === 'PASS'
                            ? 'bg-green-50'
                            : res.status === 'FAIL'
                              ? 'bg-red-50'
                              : 'bg-yellow-50'}"
                    >
                        <span class="font-medium text-gray-800">{res.msg}</span>
                    </div>
                {/each}
            </div>
        {/if}
    </div>
</div>
