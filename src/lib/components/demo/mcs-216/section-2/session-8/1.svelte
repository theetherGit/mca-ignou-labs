<script lang="ts">
    // OOP Classes (Lab Requirement)
    let title, author, copyrightDate, ISBN, pages;
    class Book {
        constructor(
            title: string,
            author: string,
            copyrightDate: Date,
            ISBN: string,
            pages: number,
        ) {
            this.title = title;
            this.author = author;
            this.copyrightDate = copyrightDate;
            this.ISBN = ISBN;
            this.pages = pages;
            this.checkoutCount = 0;
            this.discarded = false;
        }
    }

    class Manual extends Book {
        constructor(...args) {
            super(...args);
        }
        checkAndDiscardByAge() {
            const age = new Date().getFullYear() - this.copyrightDate;
            if (age > 5) this.discarded = true;
            return { age, discarded: this.discarded };
        }
    }

    class Novel extends Book {
        constructor(...args) {
            super(...args);
        }
        updateCheckoutAndCheck() {
            this.checkoutCount++;
            if (this.checkoutCount > 100) this.discarded = true;
            return { count: this.checkoutCount, discarded: this.discarded };
        }
    }

    // Reactive State
    let manualStatus = $state(null);
    let novelStatus = $state(null);
    let logs: string[] = $state([]);

    function runSimulation() {
        const manual = new Manual(
            "C++ Programming",
            "Bjarne Stroustrup",
            2018,
            "978-0321563842",
            1300,
        );
        const novel = new Novel(
            "1984",
            "George Orwell",
            1949,
            "978-0451524935",
            328,
        );

        manualStatus = manual.checkAndDiscardByAge();
        for (let i = 0; i < 101; i++) novel.updateCheckoutAndCheck();
        novelStatus = {
            count: novel.checkoutCount,
            discarded: novel.discarded,
        };

        logs = [
            `Manual "${manual.title}" age: ${manualStatus.age} yrs → ${manualStatus.discarded ? "Discarded" : "Active"}`,
            `Novel "${novel.title}" checkouts: ${novelStatus.count} → ${novelStatus.discarded ? "Discarded" : "Active"}`,
        ];
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black rounded-xl mt-5 flex flex-col items-center justify-center gap-6"
>
    <h2 class="text-2xl font-bold text-gray-800">📖 Library Book Management</h2>

    <button
        onclick={runSimulation}
        class="px-6 py-3 bg-blue-600 text-white rounded-lg hover:bg-blue-700 transition font-medium shadow-md"
    >
        Run Simulation
    </button>

    {#if manualStatus && novelStatus}
        <div class="w-full max-w-lg space-y-4">
            <!-- Manual Card -->
            <div
                class="bg-white p-5 rounded-xl shadow border-l-4 border-red-500"
            >
                <h3 class="font-semibold text-lg">📘 Manual</h3>
                <p class="text-gray-600">Age: {manualStatus.age} years</p>
                <p
                    class="mt-1 font-medium {manualStatus.discarded
                        ? 'text-red-600'
                        : 'text-green-600'}"
                >
                    {manualStatus.discarded
                        ? "❌ Discarded (Outdated >5 yrs)"
                        : "✅ Active"}
                </p>
            </div>

            <!-- Novel Card -->
            <div
                class="bg-white p-5 rounded-xl shadow border-l-4 border-blue-500"
            >
                <h3 class="font-semibold text-lg">📗 Novel</h3>
                <p class="text-gray-600">
                    Checkouts: {novelStatus.count} / 100
                </p>
                <p
                    class="mt-1 font-medium {novelStatus.discarded
                        ? 'text-red-600'
                        : 'text-green-600'}"
                >
                    {novelStatus.discarded
                        ? "❌ Discarded (>100 checkouts)"
                        : "✅ Active"}
                </p>
            </div>
        </div>
    {/if}
</div>
