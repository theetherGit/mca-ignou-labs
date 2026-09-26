<script lang="ts">
    let resultMsg = $state("");
    let isLoading = $state(false);

    class MultiplicatorUnitFailure extends Error {
        constructor(msg: string) {
            super(msg);
            this.name = "MultiplicatorUnitFailure";
        }
    }

    function primitiveMultiply(a: number, b: number) {
        if (Math.random() < 0.2) return a * b;
        throw new MultiplicatorUnitFailure("Failure");
    }

    function reliableMultiply(a: number, b: number) {
        let attempts = 0;
        while (true) {
            attempts++;
            try {
                return { result: primitiveMultiply(a, b), attempts };
            } catch (e) {
                if (!(e instanceof MultiplicatorUnitFailure)) throw e;
            }
        }
    }

    function runWrapper() {
        isLoading = true;
        resultMsg = "Calculating...";
        // Simulate async delay for UX
        setTimeout(() => {
            const { result, attempts } = reliableMultiply(6, 7);
            resultMsg = `✅ Result: ${result} (Took ${attempts} attempt${attempts > 1 ? "s" : ""})`;
            isLoading = false;
        }, 50);
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl flex flex-col items-center justify-center gap-4"
>
    <h2 class="text-xl font-semibold text-gray-800">Reliable Multiply</h2>
    <p class="text-gray-600">
        Input: <strong>6 × 7</strong> (20% success rate per attempt)
    </p>

    <button
        onclick={runWrapper}
        disabled={isLoading}
        class="px-6 py-2 bg-indigo-600 text-white rounded-lg hover:bg-indigo-700 transition disabled:opacity-50"
    >
        {isLoading ? "Retrying..." : "Run Wrapper"}
    </button>

    <p class="text-lg font-medium text-gray-700 min-h-6">{resultMsg}</p>
</div>
