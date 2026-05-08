<script lang="ts">
    let trailResult = $state("");
    let isLoading = $state(false);

    const nestData: Record<string, Record<string, string>> = {
        CrowNestA: { scalpel: "CrowNestB" },
        CrowNestB: { scalpel: "CrowNestC" },
        CrowNestC: { scalpel: "CrowNestC" },
    };

    function anyStorage(nest: string, name: string): Promise<string | null> {
        return new Promise((resolve) =>
            setTimeout(() => resolve(nestData[nest]?.[name] || null), 600),
        );
    }

    async function locateScalpel(startNest: string) {
        let current = startNest;
        let trail = [current];
        while (true) {
            const next = await anyStorage(current, "scalpel");
            if (next === current) break;
            trail.push(next as string);
            current = next as string;
        }
        return { foundAt: current, trail: trail.join(" → ") };
    }

    async function findScalpel() {
        isLoading = true;
        trailResult = "";
        const res = await locateScalpel("CrowNestA");
        trailResult = `Found at: ${res.foundAt}\n👣 Trail: ${res.trail}`;
        isLoading = false;
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black rounded-xl mt-5 flex flex-col items-center justify-center gap-6"
>
    <h2 class="text-2xl font-bold text-gray-800">🦅 Scalpel Tracker</h2>

    <button
        onclick={findScalpel}
        disabled={isLoading}
        class="px-6 py-3 bg-indigo-600 text-white rounded-lg hover:bg-indigo-700 transition disabled:opacity-50 font-medium shadow"
    >
        {isLoading ? "🔍 Tracing..." : "Find Scalpel"}
    </button>

    {#if trailResult}
        <div
            class="w-full max-w-md bg-white p-5 rounded-xl shadow-md border-l-4 border-green-500 whitespace-pre-wrap font-mono text-sm text-gray-700"
        >
            {trailResult}
        </div>
    {/if}
</div>
